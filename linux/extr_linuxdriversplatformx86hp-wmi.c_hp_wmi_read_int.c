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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HPWMI_READ ; 
 int hp_wmi_perform_query (int,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int hp_wmi_read_int(int query)
{
	int val = 0, ret;

	ret = hp_wmi_perform_query(query, HPWMI_READ, &val,
				   sizeof(val), sizeof(val));

	if (ret)
		return ret < 0 ? ret : -EINVAL;

	return val;
}