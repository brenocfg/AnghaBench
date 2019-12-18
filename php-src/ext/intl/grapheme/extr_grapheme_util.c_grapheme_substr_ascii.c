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
typedef  size_t int32_t ;

/* Variables and functions */
 size_t INT32_MAX ; 

void grapheme_substr_ascii(char *str, size_t str_len, int32_t f, int32_t l, char **sub_str, int32_t *sub_str_len)
{
	int32_t str_len2 = (int32_t)str_len; /* in order to avoid signed/unsigned problems */
    *sub_str = NULL;

    if(str_len > INT32_MAX) {
    	/* We can not return long strings from ICU functions, so we won't here too */
    	return;
    }

    if ((l < 0 && -l > str_len2)) {
        return;
    } else if (l > 0 && l > str_len2) {
        l = str_len2;
    }

    if (f > str_len2 || (f < 0 && -f > str_len2)) {
        return;
    }

    if (l < 0 && str_len2 < f - l) {
        return;
    }

    /* if "from" position is negative, count start position from the end
     * of the string
     */
    if (f < 0) {
        f = str_len2 + f;
        if (f < 0) {
            f = 0;
        }
    }


    /* if "length" position is negative, set it to the length
     * needed to stop that many chars from the end of the string
     */
    if (l < 0) {
        l = (str_len2 - f) + l;
        if (l < 0) {
            l = 0;
        }
    }

    if (f >= str_len2) {
        return;
    }

    if ((f + l) > str_len2) {
        l = str_len - f;
    }

    *sub_str = str + f;
    *sub_str_len = l;

    return;
}