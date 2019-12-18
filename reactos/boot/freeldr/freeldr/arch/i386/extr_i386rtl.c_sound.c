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
typedef  int /*<<< orphan*/  PUCHAR ;

/* Variables and functions */
 int READ_PORT_UCHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int /*<<< orphan*/ ,int) ; 

void sound(int freq)
{
    int scale;

    if (freq == 0)
    {
        WRITE_PORT_UCHAR((PUCHAR)0x61, READ_PORT_UCHAR((PUCHAR)0x61) & ~3);
        return;
    }

    scale = 1193046 / freq;
    WRITE_PORT_UCHAR((PUCHAR)0x43, 0xb6);
    WRITE_PORT_UCHAR((PUCHAR)0x42, scale & 0xff);
    WRITE_PORT_UCHAR((PUCHAR)0x42, scale >> 8);
    WRITE_PORT_UCHAR((PUCHAR)0x61, READ_PORT_UCHAR((PUCHAR)0x61) | 3);
}