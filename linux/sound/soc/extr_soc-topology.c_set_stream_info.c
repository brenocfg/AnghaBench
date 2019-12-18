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
struct snd_soc_tplg_stream_caps {int /*<<< orphan*/  sig_bits; int /*<<< orphan*/  formats; int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; int /*<<< orphan*/  rates; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  name; } ;
struct snd_soc_pcm_stream {void* sig_bits; int /*<<< orphan*/  formats; void* rate_max; void* rate_min; void* rates; void* channels_max; void* channels_min; int /*<<< orphan*/  stream_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_stream_info(struct snd_soc_pcm_stream *stream,
	struct snd_soc_tplg_stream_caps *caps)
{
	stream->stream_name = kstrdup(caps->name, GFP_KERNEL);
	stream->channels_min = le32_to_cpu(caps->channels_min);
	stream->channels_max = le32_to_cpu(caps->channels_max);
	stream->rates = le32_to_cpu(caps->rates);
	stream->rate_min = le32_to_cpu(caps->rate_min);
	stream->rate_max = le32_to_cpu(caps->rate_max);
	stream->formats = le64_to_cpu(caps->formats);
	stream->sig_bits = le32_to_cpu(caps->sig_bits);
}