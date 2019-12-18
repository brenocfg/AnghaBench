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
struct sst_runtime_stream {size_t bytes_written; int /*<<< orphan*/  id; TYPE_2__* compr_ops; } ;
struct snd_compr_stream {TYPE_1__* runtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ack ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ;} ;
struct TYPE_4__ {struct sst_runtime_stream* private_data; } ;

/* Variables and functions */
 TYPE_3__* sst ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int sst_platform_compr_ack(struct snd_compr_stream *cstream,
					size_t bytes)
{
	struct sst_runtime_stream *stream;

	stream  = cstream->runtime->private_data;
	stream->compr_ops->ack(sst->dev, stream->id, (unsigned long)bytes);
	stream->bytes_written += bytes;

	return 0;
}