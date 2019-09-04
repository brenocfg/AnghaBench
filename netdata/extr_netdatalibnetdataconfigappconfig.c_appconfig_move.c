#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct section {char* name; struct config_option* values; } ;
struct config_option {int /*<<< orphan*/  name; struct config_option* next; int /*<<< orphan*/  hash; } ;
struct config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONFIG ; 
 struct config_option* appconfig_option_index_add (struct section*,struct config_option*) ; 
 struct config_option* appconfig_option_index_del (struct section*,struct config_option*) ; 
 struct config_option* appconfig_option_index_find (struct section*,char const*,int /*<<< orphan*/ ) ; 
 struct section* appconfig_section_create (struct config*,char const*) ; 
 struct section* appconfig_section_find (struct config*,char const*) ; 
 int /*<<< orphan*/  config_section_unlock (struct section*) ; 
 int /*<<< orphan*/  config_section_wrlock (struct section*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupz (char const*) ; 
 scalar_t__ unlikely (int) ; 

int appconfig_move(struct config *root, const char *section_old, const char *name_old, const char *section_new, const char *name_new) {
    struct config_option *cv_old, *cv_new;
    int ret = -1;

    debug(D_CONFIG, "request to rename config in section '%s', old name '%s', to section '%s', new name '%s'", section_old, name_old, section_new, name_new);

    struct section *co_old = appconfig_section_find(root, section_old);
    if(!co_old) return ret;

    struct section *co_new = appconfig_section_find(root, section_new);
    if(!co_new) co_new = appconfig_section_create(root, section_new);

    config_section_wrlock(co_old);
    if(co_old != co_new)
        config_section_wrlock(co_new);

    cv_old = appconfig_option_index_find(co_old, name_old, 0);
    if(!cv_old) goto cleanup;

    cv_new = appconfig_option_index_find(co_new, name_new, 0);
    if(cv_new) goto cleanup;

    if(unlikely(appconfig_option_index_del(co_old, cv_old) != cv_old))
        error("INTERNAL ERROR: deletion of config '%s' from section '%s', deleted tge wrong config entry.", cv_old->name, co_old->name);

    if(co_old->values == cv_old) {
        co_old->values = cv_old->next;
    }
    else {
        struct config_option *t;
        for(t = co_old->values; t && t->next != cv_old ;t = t->next) ;
        if(!t || t->next != cv_old)
            error("INTERNAL ERROR: cannot find variable '%s' in section '%s' of the config - but it should be there.", cv_old->name, co_old->name);
        else
            t->next = cv_old->next;
    }

    freez(cv_old->name);
    cv_old->name = strdupz(name_new);
    cv_old->hash = simple_hash(cv_old->name);

    cv_new = cv_old;
    cv_new->next = co_new->values;
    co_new->values = cv_new;

    if(unlikely(appconfig_option_index_add(co_new, cv_old) != cv_old))
        error("INTERNAL ERROR: re-indexing of config '%s' in section '%s', already exists.", cv_old->name, co_new->name);

    ret = 0;

cleanup:
    if(co_old != co_new)
        config_section_unlock(co_new);
    config_section_unlock(co_old);
    return ret;
}