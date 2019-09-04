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
struct sh_msiof_spi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFDR ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void sh_msiof_spi_write_fifo_8(struct sh_msiof_spi_priv *p,
				      const void *tx_buf, int words, int fs)
{
	const u8 *buf_8 = tx_buf;
	int k;

	for (k = 0; k < words; k++)
		sh_msiof_write(p, TFDR, buf_8[k] << fs);
}