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
typedef  enum threshold_decrement { ____Placeholder_threshold_decrement } threshold_decrement ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MASK_OOKPEAK_THRESDEC ; 
#define  OOKPEAK_THRESHDEC_16_TIMES 143 
#define  OOKPEAK_THRESHDEC_4_TIMES 142 
#define  OOKPEAK_THRESHDEC_8_TIMES 141 
#define  OOKPEAK_THRESHDEC_EVERY_2ND 140 
#define  OOKPEAK_THRESHDEC_EVERY_4TH 139 
#define  OOKPEAK_THRESHDEC_EVERY_8TH 138 
#define  OOKPEAK_THRESHDEC_ONCE 137 
#define  OOKPEAK_THRESHDEC_TWICE 136 
 int /*<<< orphan*/  REG_OOKPEAK ; 
#define  dec_16times 135 
#define  dec_4times 134 
#define  dec_8times 133 
#define  dec_every2nd 132 
#define  dec_every4th 131 
#define  dec_every8th 130 
#define  dec_once 129 
#define  dec_twice 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int rf69_read_mod_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ unlikely (int) ; 

int rf69_set_ook_threshold_dec(struct spi_device *spi,
			       enum threshold_decrement threshold_decrement)
{
	static const u8 td_map[] = {
		[dec_every8th] = OOKPEAK_THRESHDEC_EVERY_8TH,
		[dec_every4th] = OOKPEAK_THRESHDEC_EVERY_4TH,
		[dec_every2nd] = OOKPEAK_THRESHDEC_EVERY_2ND,
		[dec_once] = OOKPEAK_THRESHDEC_ONCE,
		[dec_twice] = OOKPEAK_THRESHDEC_TWICE,
		[dec_4times] = OOKPEAK_THRESHDEC_4_TIMES,
		[dec_8times] = OOKPEAK_THRESHDEC_8_TIMES,
		[dec_16times] = OOKPEAK_THRESHDEC_16_TIMES,
	};

	if (unlikely(threshold_decrement >= ARRAY_SIZE(td_map))) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	return rf69_read_mod_write(spi, REG_OOKPEAK, MASK_OOKPEAK_THRESDEC,
				   td_map[threshold_decrement]);
}