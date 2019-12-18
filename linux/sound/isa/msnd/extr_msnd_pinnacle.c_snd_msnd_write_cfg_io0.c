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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EIO ; 
 int HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREG_IO0_BASEHI ; 
 int /*<<< orphan*/  IREG_IO0_BASELO ; 
 int /*<<< orphan*/  IREG_LOGDEVICE ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_msnd_write_cfg (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_msnd_write_cfg_io0(int cfg, int num, u16 io)
{
	if (snd_msnd_write_cfg(cfg, IREG_LOGDEVICE, num))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_IO0_BASEHI, HIBYTE(io)))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_IO0_BASELO, LOBYTE(io)))
		return -EIO;
	return 0;
}