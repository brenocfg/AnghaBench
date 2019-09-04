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
struct annotation {scalar_t__ have_cycles; TYPE_1__* options; } ;
struct TYPE_2__ {scalar_t__ show_minmax_cycle; } ;

/* Variables and functions */
 int ANNOTATION__CYCLES_WIDTH ; 
 int ANNOTATION__IPC_WIDTH ; 
 int ANNOTATION__MINMAX_CYCLES_WIDTH ; 

__attribute__((used)) static inline int annotation__cycles_width(struct annotation *notes)
{
	if (notes->have_cycles && notes->options->show_minmax_cycle)
		return ANNOTATION__IPC_WIDTH + ANNOTATION__MINMAX_CYCLES_WIDTH;

	return notes->have_cycles ? ANNOTATION__IPC_WIDTH + ANNOTATION__CYCLES_WIDTH : 0;
}