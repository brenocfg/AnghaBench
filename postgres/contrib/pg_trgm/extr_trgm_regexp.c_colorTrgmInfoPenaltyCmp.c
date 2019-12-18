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
typedef  scalar_t__ float4 ;
struct TYPE_2__ {scalar_t__ penalty; } ;
typedef  TYPE_1__ ColorTrgmInfo ;

/* Variables and functions */

__attribute__((used)) static int
colorTrgmInfoPenaltyCmp(const void *p1, const void *p2)
{
	float4		penalty1 = ((const ColorTrgmInfo *) p1)->penalty;
	float4		penalty2 = ((const ColorTrgmInfo *) p2)->penalty;

	if (penalty1 < penalty2)
		return 1;
	else if (penalty1 == penalty2)
		return 0;
	else
		return -1;
}