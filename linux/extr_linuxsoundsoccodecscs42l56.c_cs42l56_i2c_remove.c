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
struct cs42l56_private {int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct cs42l56_private* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs42l56_i2c_remove(struct i2c_client *client)
{
	struct cs42l56_private *cs42l56 = i2c_get_clientdata(client);

	regulator_bulk_disable(ARRAY_SIZE(cs42l56->supplies),
			       cs42l56->supplies);
	return 0;
}