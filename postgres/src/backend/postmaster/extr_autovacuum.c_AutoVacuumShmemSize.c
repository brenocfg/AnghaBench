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
typedef  int /*<<< orphan*/  WorkerInfoData ;
typedef  int Size ;
typedef  int /*<<< orphan*/  AutoVacuumShmemStruct ;

/* Variables and functions */
 int MAXALIGN (int) ; 
 int add_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autovacuum_max_workers ; 
 int /*<<< orphan*/  mul_size (int /*<<< orphan*/ ,int) ; 

Size
AutoVacuumShmemSize(void)
{
	Size		size;

	/*
	 * Need the fixed struct and the array of WorkerInfoData.
	 */
	size = sizeof(AutoVacuumShmemStruct);
	size = MAXALIGN(size);
	size = add_size(size, mul_size(autovacuum_max_workers,
								   sizeof(WorkerInfoData)));
	return size;
}