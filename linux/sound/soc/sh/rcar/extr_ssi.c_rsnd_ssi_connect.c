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
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {int dummy; } ;
typedef  enum rsnd_mod_type { ____Placeholder_rsnd_mod_type } rsnd_mod_type ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int RSND_MOD_SSI ; 
 int RSND_MOD_SSIM1 ; 
 int RSND_MOD_SSIM2 ; 
 int RSND_MOD_SSIM3 ; 
 int /*<<< orphan*/  rsnd_dai_connect (struct rsnd_mod*,struct rsnd_dai_stream*,int) ; 
 int /*<<< orphan*/  rsnd_io_to_mod (struct rsnd_dai_stream*,int) ; 
 struct rsnd_dai* rsnd_io_to_rdai (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_rdai_channels_set (struct rsnd_dai*,int) ; 
 int /*<<< orphan*/  rsnd_rdai_ssi_lane_set (struct rsnd_dai*,int) ; 

__attribute__((used)) static void rsnd_ssi_connect(struct rsnd_mod *mod,
			     struct rsnd_dai_stream *io)
{
	struct rsnd_dai *rdai = rsnd_io_to_rdai(io);
	enum rsnd_mod_type types[] = {
		RSND_MOD_SSI,
		RSND_MOD_SSIM1,
		RSND_MOD_SSIM2,
		RSND_MOD_SSIM3,
	};
	enum rsnd_mod_type type;
	int i;

	/* try SSI -> SSIM1 -> SSIM2 -> SSIM3 */
	for (i = 0; i < ARRAY_SIZE(types); i++) {
		type = types[i];
		if (!rsnd_io_to_mod(io, type)) {
			rsnd_dai_connect(mod, io, type);
			rsnd_rdai_channels_set(rdai, (i + 1) * 2);
			rsnd_rdai_ssi_lane_set(rdai, (i + 1));
			return;
		}
	}
}