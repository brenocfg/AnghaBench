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
struct s3fwrn5_i2c_phy {int /*<<< orphan*/  ndev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct s3fwrn5_i2c_phy* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  s3fwrn5_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3fwrn5_i2c_remove(struct i2c_client *client)
{
	struct s3fwrn5_i2c_phy *phy = i2c_get_clientdata(client);

	s3fwrn5_remove(phy->ndev);

	return 0;
}