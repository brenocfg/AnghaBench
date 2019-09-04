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
struct lp8755_chip {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int LP8755_BUCK_MAX ; 
 struct lp8755_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lp8755_write (struct lp8755_chip*,int,int) ; 

__attribute__((used)) static int lp8755_remove(struct i2c_client *client)
{
	int icnt;
	struct lp8755_chip *pchip = i2c_get_clientdata(client);

	for (icnt = 0; icnt < LP8755_BUCK_MAX; icnt++)
		lp8755_write(pchip, icnt, 0x00);

	return 0;
}