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
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TidScanState ;

/* Variables and functions */

__attribute__((used)) static bool
TidRecheck(TidScanState *node, TupleTableSlot *slot)
{
	/*
	 * XXX shouldn't we check here to make sure tuple matches TID list? In
	 * runtime-key case this is not certain, is it?  However, in the WHERE
	 * CURRENT OF case it might not match anyway ...
	 */
	return true;
}