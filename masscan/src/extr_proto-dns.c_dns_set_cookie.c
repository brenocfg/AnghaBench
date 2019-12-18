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
typedef  int uint64_t ;

/* Variables and functions */

unsigned
dns_set_cookie(unsigned char *px, size_t length, uint64_t cookie)
{
    if (length > 2) {
        px[0] = (unsigned char)(cookie >> 8);
        px[1] = (unsigned char)(cookie >> 0);
        return cookie & 0xFFFF;
    } else
        return 0;
}