#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_3__ {scalar_t__ high; } ;
struct TYPE_4__ {scalar_t__ value; TYPE_1__ part; } ;
typedef  TYPE_2__ _Int64 ;

/* Variables and functions */

double
_TIFFUInt64ToDouble(uint64 ui64)
{
	_Int64 i;

	i.value = ui64;
	if (i.part.high >= 0) {
		return (double)i.value;
	} else {
		long double df;
		df = (long double)i.value;
		df += 18446744073709551616.0; /* adding 2**64 */
		return (double)df;
	}
}