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
struct tcf_proto {int dummy; } ;
struct cls_fl_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fl_put (struct cls_fl_filter*) ; 

__attribute__((used)) static void fl_put(struct tcf_proto *tp, void *arg)
{
	struct cls_fl_filter *f = arg;

	__fl_put(f);
}