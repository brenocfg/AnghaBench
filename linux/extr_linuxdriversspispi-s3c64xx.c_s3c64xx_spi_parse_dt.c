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
struct s3c64xx_spi_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct s3c64xx_spi_info* dev_get_platdata (struct device*) ; 

__attribute__((used)) static struct s3c64xx_spi_info *s3c64xx_spi_parse_dt(struct device *dev)
{
	return dev_get_platdata(dev);
}