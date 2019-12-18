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
struct rsnd_priv {int /*<<< orphan*/  lock; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  rsnd_io_is_working (struct rsnd_dai_stream*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 scalar_t__ rsnd_src_error_occurred (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_src_status_clear (struct rsnd_mod*) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rsnd_src_interrupt(struct rsnd_mod *mod,
				 struct rsnd_dai_stream *io)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);
	bool stop = false;

	spin_lock(&priv->lock);

	/* ignore all cases if not working */
	if (!rsnd_io_is_working(io))
		goto rsnd_src_interrupt_out;

	if (rsnd_src_error_occurred(mod))
		stop = true;

	rsnd_src_status_clear(mod);
rsnd_src_interrupt_out:

	spin_unlock(&priv->lock);

	if (stop)
		snd_pcm_stop_xrun(io->substream);
}