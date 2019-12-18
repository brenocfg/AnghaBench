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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  hashtable_iter_set (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_object (int /*<<< orphan*/ *) ; 

int json_object_iter_set_new(json_t *json, void *iter, json_t *value)
{
    if(!json_is_object(json) || !iter || !value)
        return -1;

    hashtable_iter_set(iter, value);
    return 0;
}