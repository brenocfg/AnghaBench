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
typedef  scalar_t__ v ;
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static void U64TO8(unsigned char *p, u64 v)
{
    p[0] = (unsigned char)((v) & 0xff);
    p[1] = (unsigned char)((v >> 8) & 0xff);
    p[2] = (unsigned char)((v >> 16) & 0xff);
    p[3] = (unsigned char)((v >> 24) & 0xff);
    p[4] = (unsigned char)((v >> 32) & 0xff);
    p[5] = (unsigned char)((v >> 40) & 0xff);
    p[6] = (unsigned char)((v >> 48) & 0xff);
    p[7] = (unsigned char)((v >> 56) & 0xff);
}