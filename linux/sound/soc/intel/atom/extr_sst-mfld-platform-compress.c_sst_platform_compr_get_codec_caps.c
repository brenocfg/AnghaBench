#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sst_runtime_stream {TYPE_2__* compr_ops; } ;
struct snd_compr_stream {TYPE_1__* runtime; } ;
struct snd_compr_codec_caps {int dummy; } ;
struct TYPE_4__ {int (* get_codec_caps ) (struct snd_compr_codec_caps*) ;} ;
struct TYPE_3__ {struct sst_runtime_stream* private_data; } ;

/* Variables and functions */
 int stub1 (struct snd_compr_codec_caps*) ; 

__attribute__((used)) static int sst_platform_compr_get_codec_caps(struct snd_compr_stream *cstream,
					struct snd_compr_codec_caps *codec)
{
	struct sst_runtime_stream *stream =
		cstream->runtime->private_data;

	return stream->compr_ops->get_codec_caps(codec);
}