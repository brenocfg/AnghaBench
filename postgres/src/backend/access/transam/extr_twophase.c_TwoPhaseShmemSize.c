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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  GlobalTransactionData ;
typedef  int /*<<< orphan*/  GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TwoPhaseStateData ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_prepared_xacts ; 
 int /*<<< orphan*/  mul_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepXacts ; 

Size
TwoPhaseShmemSize(void)
{
	Size		size;

	/* Need the fixed struct, the array of pointers, and the GTD structs */
	size = offsetof(TwoPhaseStateData, prepXacts);
	size = add_size(size, mul_size(max_prepared_xacts,
								   sizeof(GlobalTransaction)));
	size = MAXALIGN(size);
	size = add_size(size, mul_size(max_prepared_xacts,
								   sizeof(GlobalTransactionData)));

	return size;
}