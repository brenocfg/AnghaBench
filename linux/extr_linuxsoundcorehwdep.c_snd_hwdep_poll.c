#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* poll ) (struct snd_hwdep*,struct file*,int /*<<< orphan*/ *) ;} ;
struct snd_hwdep {TYPE_1__ ops; } ;
struct file {struct snd_hwdep* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_hwdep*,struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t snd_hwdep_poll(struct file * file, poll_table * wait)
{
	struct snd_hwdep *hw = file->private_data;
	if (hw->ops.poll)
		return hw->ops.poll(hw, file, wait);
	return 0;
}