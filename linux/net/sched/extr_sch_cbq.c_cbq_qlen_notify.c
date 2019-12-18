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
struct cbq_class {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbq_deactivate_class (struct cbq_class*) ; 

__attribute__((used)) static void cbq_qlen_notify(struct Qdisc *sch, unsigned long arg)
{
	struct cbq_class *cl = (struct cbq_class *)arg;

	cbq_deactivate_class(cl);
}