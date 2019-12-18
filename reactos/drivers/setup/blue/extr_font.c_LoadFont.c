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
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/ * PUCHAR ;

/* Variables and functions */

VOID
LoadFont(
    PUCHAR Bitplane,
    PUCHAR FontBitfield)
{
    UINT32 i, j;

    for (i = 0; i < 256; i++)
    {
        for (j = 0; j < 8; j++)
        {
            *Bitplane = FontBitfield[i * 8 + j];
            Bitplane++;
        }

        // padding
        for (j = 8; j < 32; j++)
        {
            *Bitplane = 0;
            Bitplane++;
        }
    }
}