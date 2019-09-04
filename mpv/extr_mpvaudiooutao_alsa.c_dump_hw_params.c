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
struct priv {int /*<<< orphan*/  output; } ;
struct ao {int /*<<< orphan*/  log; struct priv* priv; } ;
typedef  int /*<<< orphan*/  snd_pcm_hw_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALSA_WARN (char*) ; 
 int /*<<< orphan*/  MSGL_DEBUG ; 
 int /*<<< orphan*/  mp_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int,char*) ; 
 size_t snd_output_buffer_string (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  snd_output_flush (int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_params_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_hw_params(struct ao *ao, const char *msg,
                           snd_pcm_hw_params_t *hw_params)
{
    struct priv *p = ao->priv;
    int err;

    err = snd_pcm_hw_params_dump(hw_params, p->output);
    CHECK_ALSA_WARN("Dump hwparams error");

    char *tmp = NULL;
    size_t tmp_s = snd_output_buffer_string(p->output, &tmp);
    if (tmp)
        mp_msg(ao->log, MSGL_DEBUG, "%s---\n%.*s---\n", msg, (int)tmp_s, tmp);
    snd_output_flush(p->output);
}