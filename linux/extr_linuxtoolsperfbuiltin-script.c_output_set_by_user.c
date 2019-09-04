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
struct TYPE_2__ {scalar_t__ user_set; } ;

/* Variables and functions */
 int OUTPUT_TYPE_MAX ; 
 TYPE_1__* output ; 

__attribute__((used)) static bool output_set_by_user(void)
{
	int j;
	for (j = 0; j < OUTPUT_TYPE_MAX; ++j) {
		if (output[j].user_set)
			return true;
	}
	return false;
}