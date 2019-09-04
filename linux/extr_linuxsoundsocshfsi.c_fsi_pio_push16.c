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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DODT ; 
 scalar_t__ fsi_is_enable_stream (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fsi_pio_push16(struct fsi_priv *fsi, u8 *_buf, int samples)
{
	int i;

	if (fsi_is_enable_stream(fsi)) {
		/*
		 * stream mode
		 * see
		 *	fsi_pio_push_init()
		 */
		u32 *buf = (u32 *)_buf;

		for (i = 0; i < samples / 2; i++)
			fsi_reg_write(fsi, DODT, buf[i]);
	} else {
		/* normal mode */
		u16 *buf = (u16 *)_buf;

		for (i = 0; i < samples; i++)
			fsi_reg_write(fsi, DODT, ((u32)*(buf + i) << 8));
	}
}