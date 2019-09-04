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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int EIO ; 
 int HIBYTE (scalar_t__) ; 
 int /*<<< orphan*/  IREG_LOGDEVICE ; 
 int /*<<< orphan*/  IREG_MEMBASEHI ; 
 int /*<<< orphan*/  IREG_MEMBASELO ; 
 int /*<<< orphan*/  IREG_MEMCONTROL ; 
 int LOBYTE (scalar_t__) ; 
 int MEMTYPE_16BIT ; 
 int MEMTYPE_HIADDR ; 
 scalar_t__ snd_msnd_write_cfg (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_msnd_write_cfg_mem(int cfg, int num, int mem)
{
	u16 wmem;

	mem >>= 8;
	wmem = (u16)(mem & 0xfff);
	if (snd_msnd_write_cfg(cfg, IREG_LOGDEVICE, num))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_MEMBASEHI, HIBYTE(wmem)))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_MEMBASELO, LOBYTE(wmem)))
		return -EIO;
	if (wmem && snd_msnd_write_cfg(cfg, IREG_MEMCONTROL,
				       MEMTYPE_HIADDR | MEMTYPE_16BIT))
		return -EIO;
	return 0;
}