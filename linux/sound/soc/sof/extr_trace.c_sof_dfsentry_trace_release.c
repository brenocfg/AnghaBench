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
struct snd_sof_dfsentry {struct snd_sof_dev* sdev; } ;
struct snd_sof_dev {scalar_t__ host_offset; int /*<<< orphan*/  dtrace_is_enabled; } ;
struct inode {struct snd_sof_dfsentry* i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int sof_dfsentry_trace_release(struct inode *inode, struct file *file)
{
	struct snd_sof_dfsentry *dfse = inode->i_private;
	struct snd_sof_dev *sdev = dfse->sdev;

	/* avoid duplicate traces at next open */
	if (!sdev->dtrace_is_enabled)
		sdev->host_offset = 0;

	return 0;
}