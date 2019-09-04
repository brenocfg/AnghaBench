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
struct snd_pcm_substream {size_t stream; } ;
struct audio_stream {int dummy; } ;
struct alchemy_pcm_ctx {struct audio_stream* stream; } ;

/* Variables and functions */
 struct alchemy_pcm_ctx* ss_to_ctx (struct snd_pcm_substream*) ; 

__attribute__((used)) static inline struct audio_stream *ss_to_as(struct snd_pcm_substream *ss)
{
	struct alchemy_pcm_ctx *ctx = ss_to_ctx(ss);
	return &(ctx->stream[ss->stream]);
}