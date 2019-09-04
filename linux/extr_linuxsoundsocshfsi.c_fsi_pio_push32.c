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
typedef  int /*<<< orphan*/  u32 ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DODT ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsi_pio_push32(struct fsi_priv *fsi, u8 *_buf, int samples)
{
	u32 *buf = (u32 *)_buf;
	int i;

	for (i = 0; i < samples; i++)
		fsi_reg_write(fsi, DODT, *(buf + i));
}