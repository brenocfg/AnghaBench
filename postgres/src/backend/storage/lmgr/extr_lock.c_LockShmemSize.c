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
typedef  int /*<<< orphan*/  PROCLOCK ;
typedef  int /*<<< orphan*/  LOCK ;

/* Variables and functions */
 long NLOCKENTS () ; 
 int add_size (int,int) ; 
 int hash_estimate_size (long,int) ; 

Size
LockShmemSize(void)
{
	Size		size = 0;
	long		max_table_size;

	/* lock hash table */
	max_table_size = NLOCKENTS();
	size = add_size(size, hash_estimate_size(max_table_size, sizeof(LOCK)));

	/* proclock hash table */
	max_table_size *= 2;
	size = add_size(size, hash_estimate_size(max_table_size, sizeof(PROCLOCK)));

	/*
	 * Since NLOCKENTS is only an estimate, add 10% safety margin.
	 */
	size = add_size(size, size / 10);

	return size;
}