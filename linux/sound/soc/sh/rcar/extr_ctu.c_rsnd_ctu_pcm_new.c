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
struct snd_soc_pcm_runtime {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_ctu {int /*<<< orphan*/  reset; int /*<<< orphan*/ * sv; int /*<<< orphan*/  pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCTRL_INITIALIZED ; 
 int /*<<< orphan*/  RSND_MAX_CHANNELS ; 
 int /*<<< orphan*/  rsnd_ctu_value_reset ; 
 scalar_t__ rsnd_flags_has (struct rsnd_ctu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_flags_set (struct rsnd_ctu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_kctrl_accept_anytime ; 
 int rsnd_kctrl_new_m (struct rsnd_mod*,struct rsnd_dai_stream*,struct snd_soc_pcm_runtime*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rsnd_kctrl_new_s (struct rsnd_mod*,struct rsnd_dai_stream*,struct snd_soc_pcm_runtime*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct rsnd_ctu* rsnd_mod_to_ctu (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_ctu_pcm_new(struct rsnd_mod *mod,
			    struct rsnd_dai_stream *io,
			    struct snd_soc_pcm_runtime *rtd)
{
	struct rsnd_ctu *ctu = rsnd_mod_to_ctu(mod);
	int ret;

	if (rsnd_flags_has(ctu, KCTRL_INITIALIZED))
		return 0;

	/* CTU Pass */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU Pass",
			       rsnd_kctrl_accept_anytime,
			       NULL,
			       &ctu->pass, RSND_MAX_CHANNELS,
			       0xC);

	/* ROW0 */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU SV0",
			       rsnd_kctrl_accept_anytime,
			       NULL,
			       &ctu->sv[0], RSND_MAX_CHANNELS,
			       0x00FFFFFF);
	if (ret < 0)
		return ret;

	/* ROW1 */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU SV1",
			       rsnd_kctrl_accept_anytime,
			       NULL,
			       &ctu->sv[1], RSND_MAX_CHANNELS,
			       0x00FFFFFF);
	if (ret < 0)
		return ret;

	/* ROW2 */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU SV2",
			       rsnd_kctrl_accept_anytime,
			       NULL,
			       &ctu->sv[2], RSND_MAX_CHANNELS,
			       0x00FFFFFF);
	if (ret < 0)
		return ret;

	/* ROW3 */
	ret = rsnd_kctrl_new_m(mod, io, rtd, "CTU SV3",
			       rsnd_kctrl_accept_anytime,
			       NULL,
			       &ctu->sv[3], RSND_MAX_CHANNELS,
			       0x00FFFFFF);
	if (ret < 0)
		return ret;

	/* Reset */
	ret = rsnd_kctrl_new_s(mod, io, rtd, "CTU Reset",
			       rsnd_kctrl_accept_anytime,
			       rsnd_ctu_value_reset,
			       &ctu->reset, 1);

	rsnd_flags_set(ctu, KCTRL_INITIALIZED);

	return ret;
}