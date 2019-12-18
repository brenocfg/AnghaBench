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
struct snd_opl3 {int dummy; } ;
struct snd_hwdep {struct snd_opl3* private_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_opl3_reset (struct snd_opl3*) ; 

int snd_opl3_release(struct snd_hwdep * hw, struct file *file)
{
	struct snd_opl3 *opl3 = hw->private_data;

	snd_opl3_reset(opl3);
	return 0;
}