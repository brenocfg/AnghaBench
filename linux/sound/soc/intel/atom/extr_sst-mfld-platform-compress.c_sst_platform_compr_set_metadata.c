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
struct sst_runtime_stream {int /*<<< orphan*/  id; TYPE_2__* compr_ops; } ;
struct snd_compr_stream {TYPE_1__* runtime; } ;
struct snd_compr_metadata {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int (* set_metadata ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_compr_metadata*) ;} ;
struct TYPE_4__ {struct sst_runtime_stream* private_data; } ;

/* Variables and functions */
 TYPE_3__* sst ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_compr_metadata*) ; 

__attribute__((used)) static int sst_platform_compr_set_metadata(struct snd_compr_stream *cstream,
					struct snd_compr_metadata *metadata)
{
	struct sst_runtime_stream *stream  =
		 cstream->runtime->private_data;

	return stream->compr_ops->set_metadata(sst->dev, stream->id, metadata);
}