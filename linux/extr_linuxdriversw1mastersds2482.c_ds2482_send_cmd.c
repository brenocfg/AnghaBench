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
typedef  int /*<<< orphan*/  u8 ;
struct ds2482_data {int /*<<< orphan*/  read_prt; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2482_PTR_CODE_STATUS ; 
 scalar_t__ i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ds2482_send_cmd(struct ds2482_data *pdev, u8 cmd)
{
	if (i2c_smbus_write_byte(pdev->client, cmd) < 0)
		return -1;

	pdev->read_prt = DS2482_PTR_CODE_STATUS;
	return 0;
}