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
typedef  int zip_uint8_t ;
typedef  int zip_uint32_t ;

/* Variables and functions */

zip_uint32_t
_zip_read4(const zip_uint8_t **a)
{
    zip_uint32_t ret;

    ret = ((((((zip_uint32_t)(*a)[3]<<8)+(*a)[2])<<8)+(*a)[1])<<8)+(*a)[0];
    *a += 4;

    return ret;
}