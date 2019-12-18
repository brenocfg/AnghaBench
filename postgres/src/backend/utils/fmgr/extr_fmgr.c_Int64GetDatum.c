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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 

Datum
Int64GetDatum(int64 X)
{
	int64	   *retval = (int64 *) palloc(sizeof(int64));

	*retval = X;
	return PointerGetDatum(retval);
}