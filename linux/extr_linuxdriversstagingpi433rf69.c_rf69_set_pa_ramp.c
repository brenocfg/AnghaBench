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
typedef  enum pa_ramp { ____Placeholder_pa_ramp } pa_ramp ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int EINVAL ; 
#define  PARAMP_10 157 
#define  PARAMP_100 156 
#define  PARAMP_1000 155 
#define  PARAMP_125 154 
#define  PARAMP_15 153 
#define  PARAMP_20 152 
#define  PARAMP_2000 151 
#define  PARAMP_25 150 
#define  PARAMP_250 149 
#define  PARAMP_31 148 
#define  PARAMP_3400 147 
#define  PARAMP_40 146 
#define  PARAMP_50 145 
#define  PARAMP_500 144 
#define  PARAMP_62 143 
 int /*<<< orphan*/  REG_PARAMP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
#define  ramp10 142 
#define  ramp100 141 
#define  ramp1000 140 
#define  ramp125 139 
#define  ramp15 138 
#define  ramp20 137 
#define  ramp2000 136 
#define  ramp25 135 
#define  ramp250 134 
#define  ramp31 133 
#define  ramp3400 132 
#define  ramp40 131 
#define  ramp50 130 
#define  ramp500 129 
#define  ramp62 128 
 int rf69_write_reg (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ unlikely (int) ; 

int rf69_set_pa_ramp(struct spi_device *spi, enum pa_ramp pa_ramp)
{
	static const u8 pa_ramp_map[] = {
		[ramp3400] = PARAMP_3400,
		[ramp2000] = PARAMP_2000,
		[ramp1000] = PARAMP_1000,
		[ramp500] = PARAMP_500,
		[ramp250] = PARAMP_250,
		[ramp125] = PARAMP_125,
		[ramp100] = PARAMP_100,
		[ramp62] = PARAMP_62,
		[ramp50] = PARAMP_50,
		[ramp40] = PARAMP_40,
		[ramp31] = PARAMP_31,
		[ramp25] = PARAMP_25,
		[ramp20] = PARAMP_20,
		[ramp15] = PARAMP_15,
		[ramp10] = PARAMP_10,
	};

	if (unlikely(pa_ramp >= ARRAY_SIZE(pa_ramp_map))) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	return rf69_write_reg(spi, REG_PARAMP, pa_ramp_map[pa_ramp]);
}