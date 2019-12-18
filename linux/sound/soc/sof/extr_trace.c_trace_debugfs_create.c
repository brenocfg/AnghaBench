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
struct snd_sof_dfsentry {struct snd_sof_dev* sdev; int /*<<< orphan*/  size; int /*<<< orphan*/  buf; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  area; } ;
struct snd_sof_dev {int /*<<< orphan*/  debugfs_root; TYPE_1__ dmatb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SOF_DFSENTRY_TYPE_BUF ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct snd_sof_dfsentry*,int /*<<< orphan*/ *) ; 
 struct snd_sof_dfsentry* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sof_dfs_trace_fops ; 

__attribute__((used)) static int trace_debugfs_create(struct snd_sof_dev *sdev)
{
	struct snd_sof_dfsentry *dfse;

	if (!sdev)
		return -EINVAL;

	dfse = devm_kzalloc(sdev->dev, sizeof(*dfse), GFP_KERNEL);
	if (!dfse)
		return -ENOMEM;

	dfse->type = SOF_DFSENTRY_TYPE_BUF;
	dfse->buf = sdev->dmatb.area;
	dfse->size = sdev->dmatb.bytes;
	dfse->sdev = sdev;

	debugfs_create_file("trace", 0444, sdev->debugfs_root, dfse,
			    &sof_dfs_trace_fops);

	return 0;
}