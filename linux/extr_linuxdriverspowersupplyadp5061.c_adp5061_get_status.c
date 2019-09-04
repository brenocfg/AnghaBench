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
struct adp5061_state {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5061_CHG_STATUS_1 ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int adp5061_get_status(struct adp5061_state *st,
			      u8 *status1, u8 *status2)
{
	u8 buf[2];
	int ret;

	/* CHG_STATUS1 and CHG_STATUS2 are adjacent regs */
	ret = regmap_bulk_read(st->regmap, ADP5061_CHG_STATUS_1,
			       &buf[0], 2);
	if (ret < 0)
		return ret;

	*status1 = buf[0];
	*status2 = buf[1];

	return ret;
}