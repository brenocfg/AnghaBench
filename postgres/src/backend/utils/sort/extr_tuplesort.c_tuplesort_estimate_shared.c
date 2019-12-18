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
typedef  int /*<<< orphan*/  TapeShare ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sharedsort ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_size (int,int) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tapes ; 

Size
tuplesort_estimate_shared(int nWorkers)
{
	Size		tapesSize;

	Assert(nWorkers > 0);

	/* Make sure that BufFile shared state is MAXALIGN'd */
	tapesSize = mul_size(sizeof(TapeShare), nWorkers);
	tapesSize = MAXALIGN(add_size(tapesSize, offsetof(Sharedsort, tapes)));

	return tapesSize;
}