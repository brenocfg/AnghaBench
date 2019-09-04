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
struct i2c_board_info {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcon_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	strlcpy(info->type, "olpc_dcon", I2C_NAME_SIZE);

	return 0;
}