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

/* Variables and functions */
 float INFINITY ; 
 float LOG_OFFSET_DB ; 
 float LOG_RANGE_DB ; 
 float powf (float,float const) ; 

__attribute__((used)) static float log_def_to_db(const float def)
{
	if (def >= 1.0f)
		return 0.0f;
	else if (def <= 0.0f)
		return -INFINITY;

	return -(LOG_RANGE_DB + LOG_OFFSET_DB) *
		       powf((LOG_RANGE_DB + LOG_OFFSET_DB) / LOG_OFFSET_DB,
			    -def) +
	       LOG_OFFSET_DB;
}