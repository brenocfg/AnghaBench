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
typedef  int /*<<< orphan*/  u64 ;
struct set_enable {int flag; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_enable_set ; 
 struct set_enable* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lowpan_enable_set(void *data, u64 val)
{
	struct set_enable *set_enable;

	set_enable = kzalloc(sizeof(*set_enable), GFP_KERNEL);
	if (!set_enable)
		return -ENOMEM;

	set_enable->flag = !!val;
	INIT_WORK(&set_enable->work, do_enable_set);

	schedule_work(&set_enable->work);

	return 0;
}