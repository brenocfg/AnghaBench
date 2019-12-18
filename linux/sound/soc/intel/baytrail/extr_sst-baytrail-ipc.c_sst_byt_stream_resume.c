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
struct sst_byt_stream {int /*<<< orphan*/  str_id; } ;
struct sst_byt {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_IA_RESUME_STREAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sst_byt_stream_operations (struct sst_byt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sst_byt_stream_resume(struct sst_byt *byt, struct sst_byt_stream *stream)
{
	int ret;

	ret = sst_byt_stream_operations(byt, IPC_IA_RESUME_STREAM,
					stream->str_id, 0);
	if (ret < 0)
		dev_err(byt->dev, "ipc: error failed to resume stream %d\n",
			stream->str_id);

	return ret;
}