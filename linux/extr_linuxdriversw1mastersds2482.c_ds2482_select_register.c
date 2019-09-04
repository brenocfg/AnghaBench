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
typedef  scalar_t__ u8 ;
struct ds2482_data {scalar_t__ read_prt; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2482_CMD_SET_READ_PTR ; 
 scalar_t__ i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int ds2482_select_register(struct ds2482_data *pdev, u8 read_ptr)
{
	if (pdev->read_prt != read_ptr) {
		if (i2c_smbus_write_byte_data(pdev->client,
					      DS2482_CMD_SET_READ_PTR,
					      read_ptr) < 0)
			return -1;

		pdev->read_prt = read_ptr;
	}
	return 0;
}