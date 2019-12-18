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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IREG_ACTIVATE ; 
 int /*<<< orphan*/  IREG_LOGDEVICE ; 
 int LD_ACTIVATE ; 
 scalar_t__ snd_msnd_write_cfg (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_msnd_activate_logical(int cfg, int num)
{
	if (snd_msnd_write_cfg(cfg, IREG_LOGDEVICE, num))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_ACTIVATE, LD_ACTIVATE))
		return -EIO;
	return 0;
}