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
struct tc_device {struct tc_class* classes; scalar_t__ family_updated; scalar_t__ name_updated; } ;
struct tc_class {int unupdated; struct tc_class* next; scalar_t__ name_updated; scalar_t__ updated; } ;

/* Variables and functions */
 scalar_t__ config_get_number (char*,char*,int) ; 
 int /*<<< orphan*/  tc_class_free (struct tc_device*,struct tc_class*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void tc_device_classes_cleanup(struct tc_device *d) {
    static int cleanup_every = 999;

    if(unlikely(cleanup_every > 0)) {
        cleanup_every = (int) config_get_number("plugin:tc", "cleanup unused classes every", 120);
        if(cleanup_every < 0) cleanup_every = -cleanup_every;
    }

    d->name_updated = 0;
    d->family_updated = 0;

    struct tc_class *c = d->classes;
    while(c) {
        if(unlikely(cleanup_every && c->unupdated >= cleanup_every)) {
            struct tc_class *nc = c->next;
            tc_class_free(d, c);
            c = nc;
        }
        else {
            c->updated = 0;
            c->name_updated = 0;

            c = c->next;
        }
    }
}