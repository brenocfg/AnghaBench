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
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  BrinTuple ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * palloc (scalar_t__) ; 
 int /*<<< orphan*/ * repalloc (int /*<<< orphan*/ *,scalar_t__) ; 

BrinTuple *
brin_copy_tuple(BrinTuple *tuple, Size len, BrinTuple *dest, Size *destsz)
{
	if (!destsz || *destsz == 0)
		dest = palloc(len);
	else if (len > *destsz)
	{
		dest = repalloc(dest, len);
		*destsz = len;
	}

	memcpy(dest, tuple, len);

	return dest;
}