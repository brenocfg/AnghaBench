#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int number; scalar_t__ present; } ;

/* Variables and functions */
 size_t OPT_PRINT_HEADERHEIGHT ; 
 TYPE_1__* printer_opts ; 

int
prt_header_height()
{
    if (printer_opts[OPT_PRINT_HEADERHEIGHT].present)
	return printer_opts[OPT_PRINT_HEADERHEIGHT].number;
    return 2;
}