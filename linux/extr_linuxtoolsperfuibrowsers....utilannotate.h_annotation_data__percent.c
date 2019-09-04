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
struct annotation_data {double* percent; } ;

/* Variables and functions */
 unsigned int PERCENT_MAX ; 

__attribute__((used)) static inline double annotation_data__percent(struct annotation_data *data,
					      unsigned int which)
{
	return which < PERCENT_MAX ? data->percent[which] : -1;
}