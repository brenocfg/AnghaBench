#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ds278x_info {TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_word_data (TYPE_1__*,int) ; 
 int /*<<< orphan*/  swab16 (int) ; 

__attribute__((used)) static inline int ds278x_read_reg16(struct ds278x_info *info, int reg_msb,
				    s16 *val)
{
	int ret;

	ret = i2c_smbus_read_word_data(info->client, reg_msb);
	if (ret < 0) {
		dev_err(&info->client->dev, "register read failed\n");
		return ret;
	}

	*val = swab16(ret);
	return 0;
}