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
struct snd_pcm_runtime {int dummy; } ;
struct rsnd_ssi {int /*<<< orphan*/  byte_pos; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_pcm_runtime* rsnd_io_to_runtime (struct rsnd_dai_stream*) ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_ssi_pio_pointer(struct rsnd_mod *mod,
			    struct rsnd_dai_stream *io,
			    snd_pcm_uframes_t *pointer)
{
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	struct snd_pcm_runtime *runtime = rsnd_io_to_runtime(io);

	*pointer = bytes_to_frames(runtime, READ_ONCE(ssi->byte_pos));

	return 0;
}