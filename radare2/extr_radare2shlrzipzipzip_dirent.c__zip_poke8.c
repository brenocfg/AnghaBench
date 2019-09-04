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
typedef  int /*<<< orphan*/  zip_uint8_t ;
typedef  int zip_uint64_t ;

/* Variables and functions */

void
_zip_poke8(zip_uint64_t i, zip_uint8_t **p)
{
    *((*p)++) = i&0xff;
    *((*p)++) = (i>>8)&0xff;
    *((*p)++) = (i>>16)&0xff;
    *((*p)++) = (i>>24)&0xff;
    *((*p)++) = (i>>32)&0xff;
    *((*p)++) = (i>>40)&0xff;
    *((*p)++) = (i>>48)&0xff;
    *((*p)++) = (i>>56)&0xff;
}