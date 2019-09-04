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
struct q6copp {int copp_idx; } ;

/* Variables and functions */
 int EINVAL ; 

int q6adm_get_copp_id(struct q6copp *copp)
{
	if (!copp)
		return -EINVAL;

	return copp->copp_idx;
}