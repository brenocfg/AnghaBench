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
struct rspi_data {int dummy; } ;

/* Variables and functions */
 int rspi_data_in (struct rspi_data*) ; 
 int rspi_data_out (struct rspi_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rspi_pio_transfer(struct rspi_data *rspi, const u8 *tx, u8 *rx,
			     unsigned int n)
{
	while (n-- > 0) {
		if (tx) {
			int ret = rspi_data_out(rspi, *tx++);
			if (ret < 0)
				return ret;
		}
		if (rx) {
			int ret = rspi_data_in(rspi);
			if (ret < 0)
				return ret;
			*rx++ = ret;
		}
	}

	return 0;
}