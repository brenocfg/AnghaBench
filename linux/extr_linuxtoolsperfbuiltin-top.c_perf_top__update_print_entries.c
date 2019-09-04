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
struct TYPE_2__ {scalar_t__ ws_row; } ;
struct perf_top {TYPE_1__ winsize; scalar_t__ print_entries; } ;

/* Variables and functions */
 scalar_t__ HEADER_LINE_NR ; 

__attribute__((used)) static void perf_top__update_print_entries(struct perf_top *top)
{
	top->print_entries = top->winsize.ws_row - HEADER_LINE_NR;
}