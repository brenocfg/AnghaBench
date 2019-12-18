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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransferExpandedObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED_RW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int,int) ; 

Datum
datumTransfer(Datum value, bool typByVal, int typLen)
{
	if (!typByVal && typLen == -1 &&
		VARATT_IS_EXTERNAL_EXPANDED_RW(DatumGetPointer(value)))
		value = TransferExpandedObject(value, CurrentMemoryContext);
	else
		value = datumCopy(value, typByVal, typLen);
	return value;
}