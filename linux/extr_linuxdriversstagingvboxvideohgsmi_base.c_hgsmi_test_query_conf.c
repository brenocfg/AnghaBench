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
typedef  scalar_t__ u32 ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ U32_MAX ; 
 int hgsmi_query_conf (struct gen_pool*,scalar_t__,scalar_t__*) ; 

int hgsmi_test_query_conf(struct gen_pool *ctx)
{
	u32 value = 0;
	int ret;

	ret = hgsmi_query_conf(ctx, U32_MAX, &value);
	if (ret)
		return ret;

	return value == U32_MAX ? 0 : -EIO;
}