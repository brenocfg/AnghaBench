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

/* Variables and functions */
 int /*<<< orphan*/ * added ; 
 int /*<<< orphan*/  added_obj_cmp ; 
 int /*<<< orphan*/  added_obj_hash ; 
 int /*<<< orphan*/ * lh_ADDED_OBJ_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_added(void)
{
    if (added != NULL)
        return 1;
    added = lh_ADDED_OBJ_new(added_obj_hash, added_obj_cmp);
    return added != NULL;
}