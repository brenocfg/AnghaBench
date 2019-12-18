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
typedef  scalar_t__ int32 ;
typedef  scalar_t__ MultiXactId ;

/* Variables and functions */

bool
MultiXactIdPrecedes(MultiXactId multi1, MultiXactId multi2)
{
	int32		diff = (int32) (multi1 - multi2);

	return (diff < 0);
}