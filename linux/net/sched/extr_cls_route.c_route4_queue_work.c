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
struct route4_filter {int /*<<< orphan*/  rwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  route4_delete_filter_work ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void route4_queue_work(struct route4_filter *f)
{
	tcf_queue_work(&f->rwork, route4_delete_filter_work);
}