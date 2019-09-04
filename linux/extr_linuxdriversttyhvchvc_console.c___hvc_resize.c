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
struct winsize {int dummy; } ;
struct hvc_struct {int /*<<< orphan*/  tty_resize; struct winsize ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void __hvc_resize(struct hvc_struct *hp, struct winsize ws)
{
	hp->ws = ws;
	schedule_work(&hp->tty_resize);
}