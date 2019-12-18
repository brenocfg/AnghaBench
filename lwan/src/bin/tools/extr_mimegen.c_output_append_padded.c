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
struct output {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int output_append_full (struct output*,char const*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int output_append_padded(struct output *output, const char *str)
{
    size_t str_len = strlen(str);

    if (str_len <= 8) {
        int r = output_append_full(output, str, str_len);
        if (r < 0)
            return r;

        if (str_len != 8)
            return output_append_full(output, "\0\0\0\0\0\0\0\0", 8 - str_len);

        return 0;
    }

    return -EINVAL;
}