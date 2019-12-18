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
 int mp_log2 (unsigned char) ; 

int bstr_parse_utf8_code_length(unsigned char b)
{
    if (b < 128)
        return 1;
    int bytes = 7 - mp_log2(b ^ 255);
    return (bytes >= 2 && bytes <= 4) ? bytes : -1;
}