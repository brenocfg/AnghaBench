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
typedef  scalar_t__ u32 ;
struct snd_pcm_runtime {scalar_t__ rate; } ;
struct TYPE_2__ {scalar_t__ val; } ;
struct rsnd_src {TYPE_1__ sync; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 scalar_t__ rsnd_io_converted_rate (struct rsnd_dai_stream*) ; 
 struct snd_pcm_runtime* rsnd_io_to_runtime (struct rsnd_dai_stream*) ; 
 struct rsnd_src* rsnd_mod_to_src (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_src_sync_is_enabled (struct rsnd_mod*) ; 

__attribute__((used)) static u32 rsnd_src_convert_rate(struct rsnd_dai_stream *io,
				 struct rsnd_mod *mod)
{
	struct snd_pcm_runtime *runtime = rsnd_io_to_runtime(io);
	struct rsnd_src *src = rsnd_mod_to_src(mod);
	u32 convert_rate;

	if (!runtime)
		return 0;

	if (!rsnd_src_sync_is_enabled(mod))
		return rsnd_io_converted_rate(io);

	convert_rate = src->sync.val;

	if (!convert_rate)
		convert_rate = rsnd_io_converted_rate(io);

	if (!convert_rate)
		convert_rate = runtime->rate;

	return convert_rate;
}