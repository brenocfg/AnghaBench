#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct stat {int dummy; } ;
struct dirent {scalar_t__ d_type; char* d_name; } ;
struct TYPE_7__ {int exists; scalar_t__ hash; char* name; char const* size_filename; char const* hw_sector_size_filename; int size; int hw_sector_size; struct TYPE_7__* next; } ;
struct TYPE_6__ {int logged_error; TYPE_2__* disks; scalar_t__ all_disks_total; } ;
typedef  int /*<<< orphan*/  DIR ;
typedef  TYPE_1__ BTRFS_NODE ;
typedef  TYPE_2__ BTRFS_DISK ;

/* Variables and functions */
 scalar_t__ DT_LNK ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  btrfs_free_disk (TYPE_2__*) ; 
 TYPE_2__* callocz (int,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 scalar_t__ read_single_number_file (char const*,int*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ simple_hash (char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int find_btrfs_disks(BTRFS_NODE *node, const char *path) {
    char filename[FILENAME_MAX + 1];

    node->all_disks_total = 0;

    BTRFS_DISK *d;
    for(d = node->disks ; d ; d = d->next)
        d->exists = 0;

    DIR *dir = opendir(path);
    if (!dir) {
        if(!node->logged_error) {
            error("BTRFS: Cannot open directory '%s'.", path);
            node->logged_error = 1;
        }
        return 1;
    }
    node->logged_error = 0;

    struct dirent *de = NULL;
    while ((de = readdir(dir))) {
        if (de->d_type != DT_LNK
            || !strcmp(de->d_name, ".")
            || !strcmp(de->d_name, "..")
                ) {
            // info("BTRFS: ignoring '%s'", de->d_name);
            continue;
        }

        uint32_t hash = simple_hash(de->d_name);

        // --------------------------------------------------------------------
        // search for it

        for(d = node->disks ; d ; d = d->next) {
            if(hash == d->hash && !strcmp(de->d_name, d->name))
                break;
        }

        // --------------------------------------------------------------------
        // did we find it?

        if(!d) {
            d = callocz(sizeof(BTRFS_DISK), 1);

            d->name = strdupz(de->d_name);
            d->hash = simple_hash(d->name);

            snprintfz(filename, FILENAME_MAX, "%s/%s/size", path, de->d_name);
            d->size_filename = strdupz(filename);

            // for bcache
            snprintfz(filename, FILENAME_MAX, "%s/%s/bcache/../queue/hw_sector_size", path, de->d_name);
            struct stat sb;
            if(stat(filename, &sb) == -1) {
                // for disks
                snprintfz(filename, FILENAME_MAX, "%s/%s/queue/hw_sector_size", path, de->d_name);
                if(stat(filename, &sb) == -1)
                    // for partitions
                    snprintfz(filename, FILENAME_MAX, "%s/%s/../queue/hw_sector_size", path, de->d_name);
            }

            d->hw_sector_size_filename = strdupz(filename);

            // link it
            d->next = node->disks;
            node->disks = d;
        }

        d->exists = 1;


        // --------------------------------------------------------------------
        // update the values

        if(read_single_number_file(d->size_filename, &d->size) != 0) {
            error("BTRFS: failed to read '%s'", d->size_filename);
            d->exists = 0;
            continue;
        }

        if(read_single_number_file(d->hw_sector_size_filename, &d->hw_sector_size) != 0) {
            error("BTRFS: failed to read '%s'", d->hw_sector_size_filename);
            d->exists = 0;
            continue;
        }

        node->all_disks_total += d->size * d->hw_sector_size;
    }
    closedir(dir);

    // ------------------------------------------------------------------------
    // cleanup

    BTRFS_DISK *last = NULL;
    d = node->disks;

    while(d) {
        if(unlikely(!d->exists)) {
            if(unlikely(node->disks == d)) {
                node->disks = d->next;
                btrfs_free_disk(d);
                d = node->disks;
                last = NULL;
            }
            else {
                last->next = d->next;
                btrfs_free_disk(d);
                d = last->next;
            }

            continue;
        }

        last = d;
        d = d->next;
    }

    return 0;
}