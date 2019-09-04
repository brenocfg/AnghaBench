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
struct section {struct section* next; int /*<<< orphan*/  name; int /*<<< orphan*/  values_index; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hash; } ;
struct config {struct section* sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONFIG ; 
 struct section* appconfig_index_add (struct config*,struct section*) ; 
 int /*<<< orphan*/  appconfig_option_compare ; 
 int /*<<< orphan*/  appconfig_unlock (struct config*) ; 
 int /*<<< orphan*/  appconfig_wrlock (struct config*) ; 
 int /*<<< orphan*/  avl_init_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct section* callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupz (char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct section *appconfig_section_create(struct config *root, const char *section) {
    debug(D_CONFIG, "Creating section '%s'.", section);

    struct section *co = callocz(1, sizeof(struct section));
    co->name = strdupz(section);
    co->hash = simple_hash(co->name);
    netdata_mutex_init(&co->mutex);

    avl_init_lock(&co->values_index, appconfig_option_compare);

    if(unlikely(appconfig_index_add(root, co) != co))
        error("INTERNAL ERROR: indexing of section '%s', already exists.", co->name);

    appconfig_wrlock(root);
    struct section *co2 = root->sections;
    if(co2) {
        while (co2->next) co2 = co2->next;
        co2->next = co;
    }
    else root->sections = co;
    appconfig_unlock(root);

    return co;
}