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
typedef  int Size ;
typedef  int /*<<< orphan*/  LogicalRepWorker ;
typedef  int /*<<< orphan*/  LogicalRepCtxStruct ;

/* Variables and functions */
 int MAXALIGN (int) ; 
 int add_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_logical_replication_workers ; 
 int /*<<< orphan*/  mul_size (int /*<<< orphan*/ ,int) ; 

Size
ApplyLauncherShmemSize(void)
{
	Size		size;

	/*
	 * Need the fixed struct and the array of LogicalRepWorker.
	 */
	size = sizeof(LogicalRepCtxStruct);
	size = MAXALIGN(size);
	size = add_size(size, mul_size(max_logical_replication_workers,
								   sizeof(LogicalRepWorker)));
	return size;
}