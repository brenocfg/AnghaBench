#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ numRight; scalar_t__ numLeft; } ;
typedef  TYPE_1__* SetOpStatePerGroup ;

/* Variables and functions */

__attribute__((used)) static inline void
initialize_counts(SetOpStatePerGroup pergroup)
{
	pergroup->numLeft = pergroup->numRight = 0;
}