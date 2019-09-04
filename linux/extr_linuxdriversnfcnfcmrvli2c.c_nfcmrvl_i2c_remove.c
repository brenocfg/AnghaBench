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
struct nfcmrvl_i2c_drv_data {int /*<<< orphan*/  priv; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct nfcmrvl_i2c_drv_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  nfcmrvl_nci_unregister_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfcmrvl_i2c_remove(struct i2c_client *client)
{
	struct nfcmrvl_i2c_drv_data *drv_data = i2c_get_clientdata(client);

	nfcmrvl_nci_unregister_dev(drv_data->priv);

	return 0;
}