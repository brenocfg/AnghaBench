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
struct ui_progress {int next; int step; int total; } ;

/* Variables and functions */
 int SLtt_Screen_Cols ; 

__attribute__((used)) static void __tui_progress__init(struct ui_progress *p)
{
	p->next = p->step = p->total / (SLtt_Screen_Cols - 2) ?: 1;
}