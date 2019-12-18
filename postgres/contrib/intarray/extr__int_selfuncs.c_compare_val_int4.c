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
typedef  int int32 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
compare_val_int4(const void *a, const void *b)
{
	int32		key = *(int32 *) a;
	const Datum *t = (const Datum *) b;

	return key - DatumGetInt32(*t);
}