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
struct tps6598x {int /*<<< orphan*/  port; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct tps6598x* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  tps6598x_disconnect (struct tps6598x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps6598x_remove(struct i2c_client *client)
{
	struct tps6598x *tps = i2c_get_clientdata(client);

	tps6598x_disconnect(tps, 0);
	typec_unregister_port(tps->port);

	return 0;
}