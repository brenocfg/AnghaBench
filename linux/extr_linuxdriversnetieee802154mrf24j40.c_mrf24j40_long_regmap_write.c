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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int*,void const*,size_t) ; 
 int spi_write (struct spi_device*,int*,size_t) ; 

__attribute__((used)) static int mrf24j40_long_regmap_write(void *context, const void *data,
				      size_t count)
{
	struct spi_device *spi = context;
	u8 buf[3];

	if (count > 3)
		return -EINVAL;

	/* regmap supports read/write mask only in frist byte
	 * long write access need to set the 12th bit, so we
	 * make special handling for write.
	 */
	memcpy(buf, data, count);
	buf[1] |= (1 << 4);

	return spi_write(spi, buf, count);
}