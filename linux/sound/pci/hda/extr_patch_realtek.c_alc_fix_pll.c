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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int pll_coef_bit; int /*<<< orphan*/  pll_coef_idx; scalar_t__ pll_nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_update_coefex_idx (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_fix_pll(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;

	if (spec->pll_nid)
		alc_update_coefex_idx(codec, spec->pll_nid, spec->pll_coef_idx,
				      1 << spec->pll_coef_bit, 0);
}