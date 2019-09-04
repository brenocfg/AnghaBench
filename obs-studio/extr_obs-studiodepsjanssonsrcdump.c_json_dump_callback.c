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
typedef  int /*<<< orphan*/  json_dump_callback_t ;

/* Variables and functions */
 size_t JSON_ENCODE_ANY ; 
 int do_dump (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  json_is_array (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_is_object (int /*<<< orphan*/  const*) ; 

int json_dump_callback(const json_t *json, json_dump_callback_t callback, void *data, size_t flags)
{
    if(!(flags & JSON_ENCODE_ANY)) {
        if(!json_is_array(json) && !json_is_object(json))
           return -1;
    }

    return do_dump(json, flags, 0, callback, data);
}