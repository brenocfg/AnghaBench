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
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  enum dagc { ____Placeholder_dagc } dagc ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  DAGC_IMPROVED_LOWBETA0 133 
#define  DAGC_IMPROVED_LOWBETA1 132 
#define  DAGC_NORMAL 131 
 int EINVAL ; 
 int /*<<< orphan*/  REG_TESTDAGC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
#define  improve 130 
#define  improve_for_low_modulation_index 129 
#define  normal_mode 128 
 int rf69_write_reg (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ unlikely (int) ; 

int rf69_set_dagc(struct spi_device *spi, enum dagc dagc)
{
	static const u8 dagc_map[] = {
		[normal_mode] = DAGC_NORMAL,
		[improve] = DAGC_IMPROVED_LOWBETA0,
		[improve_for_low_modulation_index] = DAGC_IMPROVED_LOWBETA1,
	};

	if (unlikely(dagc >= ARRAY_SIZE(dagc_map))) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	return rf69_write_reg(spi, REG_TESTDAGC, dagc_map[dagc]);
}