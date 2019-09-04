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
struct process_filter {scalar_t__ pid; struct process_filter* next; int /*<<< orphan*/  name; } ;
struct per_pidcomm {int /*<<< orphan*/  comm; } ;
struct per_pid {scalar_t__ pid; } ;

/* Variables and functions */
 struct process_filter* process_filter ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int passes_filter(struct per_pid *p, struct per_pidcomm *c)
{
	struct process_filter *filt;
	if (!process_filter)
		return 1;

	filt = process_filter;
	while (filt) {
		if (filt->pid && p->pid == filt->pid)
			return 1;
		if (strcmp(filt->name, c->comm) == 0)
			return 1;
		filt = filt->next;
	}
	return 0;
}