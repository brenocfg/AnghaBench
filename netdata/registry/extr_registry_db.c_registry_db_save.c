#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* db_filename; scalar_t__ log_count; int /*<<< orphan*/  machines_urls_count; int /*<<< orphan*/  persons_urls_count; int /*<<< orphan*/  urls_count; scalar_t__ usages_count; int /*<<< orphan*/  machines_count; int /*<<< orphan*/  persons_count; int /*<<< orphan*/  persons; int /*<<< orphan*/  machines; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,...) ; 
 int dictionary_get_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_log_limit_reset () ; 
 int /*<<< orphan*/  error_log_limit_unlimited () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int link (char*,char*) ; 
 TYPE_1__ registry ; 
 int /*<<< orphan*/  registry_db_should_be_saved () ; 
 int /*<<< orphan*/  registry_log_recreate () ; 
 int /*<<< orphan*/  registry_machine_save ; 
 int /*<<< orphan*/  registry_person_save ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int unlink (char*) ; 

int registry_db_save(void) {
    if(unlikely(!registry.enabled))
        return -1;

    if(unlikely(!registry_db_should_be_saved()))
        return -2;

    error_log_limit_unlimited();

    char tmp_filename[FILENAME_MAX + 1];
    char old_filename[FILENAME_MAX + 1];

    snprintfz(old_filename, FILENAME_MAX, "%s.old", registry.db_filename);
    snprintfz(tmp_filename, FILENAME_MAX, "%s.tmp", registry.db_filename);

    debug(D_REGISTRY, "Registry: Creating file '%s'", tmp_filename);
    FILE *fp = fopen(tmp_filename, "w");
    if(!fp) {
        error("Registry: Cannot create file: %s", tmp_filename);
        error_log_limit_reset();
        return -1;
    }

    // dictionary_get_all() has its own locking, so this is safe to do

    debug(D_REGISTRY, "Saving all machines");
    int bytes1 = dictionary_get_all(registry.machines, registry_machine_save, fp);
    if(bytes1 < 0) {
        error("Registry: Cannot save registry machines - return value %d", bytes1);
        fclose(fp);
        error_log_limit_reset();
        return bytes1;
    }
    debug(D_REGISTRY, "Registry: saving machines took %d bytes", bytes1);

    debug(D_REGISTRY, "Saving all persons");
    int bytes2 = dictionary_get_all(registry.persons, registry_person_save, fp);
    if(bytes2 < 0) {
        error("Registry: Cannot save registry persons - return value %d", bytes2);
        fclose(fp);
        error_log_limit_reset();
        return bytes2;
    }
    debug(D_REGISTRY, "Registry: saving persons took %d bytes", bytes2);

    // save the totals
    fprintf(fp, "T\t%016llx\t%016llx\t%016llx\t%016llx\t%016llx\t%016llx\n",
            registry.persons_count,
            registry.machines_count,
            registry.usages_count + 1, // this is required - it is lost on db rotation
            registry.urls_count,
            registry.persons_urls_count,
            registry.machines_urls_count
    );

    fclose(fp);

    errno = 0;

    // remove the .old db
    debug(D_REGISTRY, "Registry: Removing old db '%s'", old_filename);
    if(unlink(old_filename) == -1 && errno != ENOENT)
        error("Registry: cannot remove old registry file '%s'", old_filename);

    // rename the db to .old
    debug(D_REGISTRY, "Registry: Link current db '%s' to .old: '%s'", registry.db_filename, old_filename);
    if(link(registry.db_filename, old_filename) == -1 && errno != ENOENT)
        error("Registry: cannot move file '%s' to '%s'. Saving registry DB failed!", registry.db_filename, old_filename);

    else {
        // remove the database (it is saved in .old)
        debug(D_REGISTRY, "Registry: removing db '%s'", registry.db_filename);
        if (unlink(registry.db_filename) == -1 && errno != ENOENT)
            error("Registry: cannot remove old registry file '%s'", registry.db_filename);

        // move the .tmp to make it active
        debug(D_REGISTRY, "Registry: linking tmp db '%s' to active db '%s'", tmp_filename, registry.db_filename);
        if (link(tmp_filename, registry.db_filename) == -1) {
            error("Registry: cannot move file '%s' to '%s'. Saving registry DB failed!", tmp_filename,
                    registry.db_filename);

            // move the .old back
            debug(D_REGISTRY, "Registry: linking old db '%s' to active db '%s'", old_filename, registry.db_filename);
            if(link(old_filename, registry.db_filename) == -1)
                error("Registry: cannot move file '%s' to '%s'. Recovering the old registry DB failed!", old_filename, registry.db_filename);
        }
        else {
            debug(D_REGISTRY, "Registry: removing tmp db '%s'", tmp_filename);
            if(unlink(tmp_filename) == -1)
                error("Registry: cannot remove tmp registry file '%s'", tmp_filename);

            // it has been moved successfully
            // discard the current registry log
            registry_log_recreate();
            registry.log_count = 0;
        }
    }

    // continue operations
    error_log_limit_reset();

    return -1;
}