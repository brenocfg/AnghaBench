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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  BL_COLOR ;

/* Variables and functions */
 int ConsoleEfiTextGetEfiColorBackground (int /*<<< orphan*/ ) ; 
 int ConsoleEfiTextGetEfiColorForeground (int /*<<< orphan*/ ) ; 

ULONG
ConsoleEfiTextGetAttribute (
    BL_COLOR BgColor,
    BL_COLOR FgColor
    )
{
    /* Convert each part and OR into a single attribute */
    return ConsoleEfiTextGetEfiColorBackground(BgColor) |
           ConsoleEfiTextGetEfiColorForeground(FgColor);
}