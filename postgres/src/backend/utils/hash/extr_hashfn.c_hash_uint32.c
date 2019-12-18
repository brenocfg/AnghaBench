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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  UInt32GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  final (scalar_t__,scalar_t__,scalar_t__) ; 

Datum
hash_uint32(uint32 k)
{
	uint32		a,
				b,
				c;

	a = b = c = 0x9e3779b9 + (uint32) sizeof(uint32) + 3923095;
	a += k;

	final(a, b, c);

	/* report the result */
	return UInt32GetDatum(c);
}