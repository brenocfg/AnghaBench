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
struct tc_device {char enabled; struct tc_device* prev; struct tc_device* next; int /*<<< orphan*/  id; int /*<<< orphan*/  classes_index; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TC_LOOP ; 
 int /*<<< orphan*/  avl_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tc_device* callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupz (char*) ; 
 int /*<<< orphan*/  tc_class_compare ; 
 struct tc_device* tc_device_index_add (struct tc_device*) ; 
 struct tc_device* tc_device_index_find (char*,int /*<<< orphan*/ ) ; 
 struct tc_device* tc_device_root ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct tc_device *tc_device_create(char *id)
{
    struct tc_device *d = tc_device_index_find(id, 0);

    if(!d) {
        debug(D_TC_LOOP, "TC: Creating device '%s'", id);

        d = callocz(1, sizeof(struct tc_device));

        d->id = strdupz(id);
        d->hash = simple_hash(d->id);
        d->enabled = (char)-1;

        avl_init(&d->classes_index, tc_class_compare);
        if(unlikely(tc_device_index_add(d) != d))
            error("plugin_tc: INTERNAL ERROR: removing device '%s' removed a different device.", d->id);

        if(!tc_device_root) {
            tc_device_root = d;
        }
        else {
            d->next = tc_device_root;
            tc_device_root->prev = d;
            tc_device_root = d;
        }
    }

    return(d);
}