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
 int mp_input_get_key_from_name (char*) ; 
 char* strchr (char*,char) ; 

int mp_input_get_keys_from_string(char *name, int max_num_keys,
                                  int *out_num_keys, int *keys)
{
    char *end, *ptr;
    int n = 0;

    ptr = name;
    n = 0;
    for (end = strchr(ptr, '-'); ; end = strchr(ptr, '-')) {
        if (end && end[1] != '\0') {
            if (end[1] == '-')
                end = &end[1];
            end[0] = '\0';
        }
        keys[n] = mp_input_get_key_from_name(ptr);
        if (keys[n] < 0)
            return 0;
        n++;
        if (end && end[1] != '\0' && n < max_num_keys)
            ptr = &end[1];
        else
            break;
    }
    *out_num_keys = n;
    return 1;
}