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
struct sigmadsp_ops {int dummy; } ;
struct sigmadsp {int /*<<< orphan*/  read; int /*<<< orphan*/  write; struct i2c_client* control_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sigmadsp*) ; 
 struct sigmadsp* devm_sigmadsp_init (int /*<<< orphan*/ *,struct sigmadsp_ops const*,char const*) ; 
 int /*<<< orphan*/  sigmadsp_read_i2c ; 
 int /*<<< orphan*/  sigmadsp_write_i2c ; 

struct sigmadsp *devm_sigmadsp_init_i2c(struct i2c_client *client,
	const struct sigmadsp_ops *ops,	const char *firmware_name)
{
	struct sigmadsp *sigmadsp;

	sigmadsp = devm_sigmadsp_init(&client->dev, ops, firmware_name);
	if (IS_ERR(sigmadsp))
		return sigmadsp;

	sigmadsp->control_data = client;
	sigmadsp->write = sigmadsp_write_i2c;
	sigmadsp->read = sigmadsp_read_i2c;

	return sigmadsp;
}