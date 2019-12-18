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
 void* hashtable_key_to_iter (char const*) ; 

void *json_object_key_to_iter(const char *key)
{
    if(!key)
        return NULL;

    return hashtable_key_to_iter(key);
}