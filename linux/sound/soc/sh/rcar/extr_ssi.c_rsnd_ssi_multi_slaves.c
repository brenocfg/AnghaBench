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
typedef  int u32 ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
typedef  enum rsnd_mod_type { ____Placeholder_rsnd_mod_type } rsnd_mod_type ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int RSND_MOD_SSIM1 ; 
 int RSND_MOD_SSIM2 ; 
 int RSND_MOD_SSIM3 ; 
 struct rsnd_mod* rsnd_io_to_mod (struct rsnd_dai_stream*,int) ; 
 int rsnd_mod_id (struct rsnd_mod*) ; 

__attribute__((used)) static u32 rsnd_ssi_multi_slaves(struct rsnd_dai_stream *io)
{
	struct rsnd_mod *mod;
	enum rsnd_mod_type types[] = {
		RSND_MOD_SSIM1,
		RSND_MOD_SSIM2,
		RSND_MOD_SSIM3,
	};
	int i, mask;

	mask = 0;
	for (i = 0; i < ARRAY_SIZE(types); i++) {
		mod = rsnd_io_to_mod(io, types[i]);
		if (!mod)
			continue;

		mask |= 1 << rsnd_mod_id(mod);
	}

	return mask;
}