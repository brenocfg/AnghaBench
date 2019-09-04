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

unsigned short
AMF_DecodeInt16(const char *data)
{
    unsigned char *c = (unsigned char *) data;
    unsigned short val;
    val = (c[0] << 8) | c[1];
    return val;
}