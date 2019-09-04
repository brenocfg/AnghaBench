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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int pcm1789_common_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcm1789_i2c_remove(struct i2c_client *client)
{
	return pcm1789_common_exit(&client->dev);
}