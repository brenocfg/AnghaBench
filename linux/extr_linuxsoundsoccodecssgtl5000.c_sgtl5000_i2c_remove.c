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
struct sgtl5000_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; int /*<<< orphan*/  mclk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sgtl5000_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sgtl5000_i2c_remove(struct i2c_client *client)
{
	struct sgtl5000_priv *sgtl5000 = i2c_get_clientdata(client);

	clk_disable_unprepare(sgtl5000->mclk);
	regulator_bulk_disable(sgtl5000->num_supplies, sgtl5000->supplies);
	regulator_bulk_free(sgtl5000->num_supplies, sgtl5000->supplies);

	return 0;
}