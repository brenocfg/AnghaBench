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
struct tc_device {struct tc_device* family; struct tc_device* name; struct tc_device* id; scalar_t__ classes; struct tc_device* prev; struct tc_device* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,struct tc_device*) ; 
 int /*<<< orphan*/  freez (struct tc_device*) ; 
 int /*<<< orphan*/  tc_class_free (struct tc_device*,scalar_t__) ; 
 struct tc_device* tc_device_index_del (struct tc_device*) ; 
 struct tc_device* tc_device_root ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void tc_device_free(struct tc_device *n)
{
    if(n->next) n->next->prev = n->prev;
    if(n->prev) n->prev->next = n->next;
    if(tc_device_root == n) {
        if(n->next) tc_device_root = n->next;
        else tc_device_root = n->prev;
    }

    if(unlikely(tc_device_index_del(n) != n))
        error("plugin_tc: INTERNAL ERROR: removing device '%s' removed a different device.", n->id);

    while(n->classes) tc_class_free(n, n->classes);

    freez(n->id);
    freez(n->name);
    freez(n->family);
    freez(n);
}