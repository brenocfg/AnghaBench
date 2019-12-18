#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sst_runtime_stream {int /*<<< orphan*/  id; TYPE_2__* compr_ops; } ;
struct snd_compr_tstamp {int byte_offset; int copied_total; } ;
struct snd_compr_stream {TYPE_1__* runtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* tstamp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_compr_tstamp*) ;} ;
struct TYPE_4__ {scalar_t__ buffer_size; struct sst_runtime_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 TYPE_3__* sst ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_compr_tstamp*) ; 

__attribute__((used)) static int sst_platform_compr_pointer(struct snd_compr_stream *cstream,
					struct snd_compr_tstamp *tstamp)
{
	struct sst_runtime_stream *stream;

	stream  = cstream->runtime->private_data;
	stream->compr_ops->tstamp(sst->dev, stream->id, tstamp);
	tstamp->byte_offset = tstamp->copied_total %
				 (u32)cstream->runtime->buffer_size;
	pr_debug("calc bytes offset/copied bytes as %d\n", tstamp->byte_offset);
	return 0;
}