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
typedef  int /*<<< orphan*/  u32 ;
struct sh_msiof_spi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFDR ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sh_msiof_read (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swab32 (int) ; 

__attribute__((used)) static void sh_msiof_spi_read_fifo_s32u(struct sh_msiof_spi_priv *p,
				       void *rx_buf, int words, int fs)
{
	u32 *buf_32 = rx_buf;
	int k;

	for (k = 0; k < words; k++)
		put_unaligned(swab32(sh_msiof_read(p, RFDR) >> fs), &buf_32[k]);
}