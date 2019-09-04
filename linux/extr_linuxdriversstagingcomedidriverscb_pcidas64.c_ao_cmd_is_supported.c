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
struct pcidas64_board {scalar_t__ layout; scalar_t__ ao_nchan; } ;

/* Variables and functions */
 scalar_t__ LAYOUT_4020 ; 

__attribute__((used)) static inline int ao_cmd_is_supported(const struct pcidas64_board *board)
{
	return board->ao_nchan && board->layout != LAYOUT_4020;
}