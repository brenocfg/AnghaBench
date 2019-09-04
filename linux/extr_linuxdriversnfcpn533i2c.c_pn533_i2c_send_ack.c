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
typedef  int u8 ;
struct pn533_i2c_phy {struct i2c_client* i2c_dev; } ;
struct pn533 {struct pn533_i2c_phy* phy; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int i2c_master_send (struct i2c_client*,int const*,int) ; 

__attribute__((used)) static int pn533_i2c_send_ack(struct pn533 *dev, gfp_t flags)
{
	struct pn533_i2c_phy *phy = dev->phy;
	struct i2c_client *client = phy->i2c_dev;
	static const u8 ack[6] = {0x00, 0x00, 0xff, 0x00, 0xff, 0x00};
	/* spec 6.2.1.3:  Preamble, SoPC (2), ACK Code (2), Postamble */
	int rc;

	rc = i2c_master_send(client, ack, 6);

	return rc;
}