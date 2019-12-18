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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */

__attribute__((used)) static void regs_to_str( unsigned int *regs, unsigned int len, WCHAR *buffer )
{
    unsigned int i;
    unsigned char *p = (unsigned char *)regs;

    for (i = 0; i < len; i++) { buffer[i] = *p++; }
    buffer[i] = 0;
}