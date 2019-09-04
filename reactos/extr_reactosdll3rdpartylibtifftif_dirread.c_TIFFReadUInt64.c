#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_2__ {int /*<<< orphan*/  l; int /*<<< orphan*/ * c; } ;
typedef  TYPE_1__ UInt64Aligned_t ;

/* Variables and functions */

__attribute__((used)) static uint64 TIFFReadUInt64(const uint8 *value)
{
	UInt64Aligned_t result;

	result.c[0]=value[0];
	result.c[1]=value[1];
	result.c[2]=value[2];
	result.c[3]=value[3];
	result.c[4]=value[4];
	result.c[5]=value[5];
	result.c[6]=value[6];
	result.c[7]=value[7];

	return result.l;
}