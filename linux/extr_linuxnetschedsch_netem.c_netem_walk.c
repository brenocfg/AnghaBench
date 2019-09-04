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
struct qdisc_walker {int stop; scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct Qdisc*,int,struct qdisc_walker*) ;} ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct Qdisc*,int,struct qdisc_walker*) ; 

__attribute__((used)) static void netem_walk(struct Qdisc *sch, struct qdisc_walker *walker)
{
	if (!walker->stop) {
		if (walker->count >= walker->skip)
			if (walker->fn(sch, 1, walker) < 0) {
				walker->stop = 1;
				return;
			}
		walker->count++;
	}
}