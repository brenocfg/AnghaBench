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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cht_int33fe_check_for_max17047 ; 
 int /*<<< orphan*/  i2c_for_each_dev (struct i2c_client**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i2c_client *cht_int33fe_find_max17047(void)
{
	struct i2c_client *max17047 = NULL;

	i2c_for_each_dev(&max17047, cht_int33fe_check_for_max17047);
	return max17047;
}