#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int str_id; } ;
struct sst_runtime_stream {TYPE_3__* ops; TYPE_2__ stream_info; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_12__ {TYPE_5__* dev; } ;
struct TYPE_11__ {TYPE_4__* driver; } ;
struct TYPE_10__ {int /*<<< orphan*/  owner; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* close ) (TYPE_5__*,int) ;} ;
struct TYPE_7__ {struct sst_runtime_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sst_runtime_stream*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_down_sst (struct sst_runtime_stream*) ; 
 TYPE_6__* sst ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int) ; 

__attribute__((used)) static void sst_media_close(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct sst_runtime_stream *stream;
	int str_id;

	stream = substream->runtime->private_data;
	power_down_sst(stream);

	str_id = stream->stream_info.str_id;
	if (str_id)
		stream->ops->close(sst->dev, str_id);
	module_put(sst->dev->driver->owner);
	kfree(stream);
}