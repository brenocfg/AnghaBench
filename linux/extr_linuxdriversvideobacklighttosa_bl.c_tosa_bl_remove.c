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
struct tosa_bl_data {int /*<<< orphan*/ * bl; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct tosa_bl_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int tosa_bl_remove(struct i2c_client *client)
{
	struct tosa_bl_data *data = i2c_get_clientdata(client);

	data->bl = NULL;
	return 0;
}