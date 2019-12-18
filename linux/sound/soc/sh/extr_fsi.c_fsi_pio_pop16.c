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
typedef  scalar_t__ u16 ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIDT ; 
 int fsi_reg_read (struct fsi_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsi_pio_pop16(struct fsi_priv *fsi, u8 *_buf, int samples)
{
	u16 *buf = (u16 *)_buf;
	int i;

	for (i = 0; i < samples; i++)
		*(buf + i) = (u16)(fsi_reg_read(fsi, DIDT) >> 8);
}