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

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IDA (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  IDA_BUG_ON (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ida ; 
 int ida_alloc_min (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_is_empty (int /*<<< orphan*/ *) ; 

void ida_check_nomem(void)
{
	DEFINE_IDA(ida);
	int id;

	id = ida_alloc_min(&ida, 256, GFP_NOWAIT);
	IDA_BUG_ON(&ida, id != -ENOMEM);
	id = ida_alloc_min(&ida, 1UL << 30, GFP_NOWAIT);
	IDA_BUG_ON(&ida, id != -ENOMEM);
	IDA_BUG_ON(&ida, !ida_is_empty(&ida));
}