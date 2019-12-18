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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {unsigned int* vnode_lvol; unsigned int* vnode_rvol; } ;
typedef  scalar_t__ hda_nid_t ;
struct TYPE_2__ {int /*<<< orphan*/ * reqs; int /*<<< orphan*/  mid; } ;

/* Variables and functions */
 unsigned int DSP_VOL_IN ; 
 unsigned int DSP_VOL_OUT ; 
 int /*<<< orphan*/  FLOAT_ZERO ; 
 scalar_t__ VNID_SPK ; 
 scalar_t__ VNODE_START_NID ; 
 TYPE_1__* ca0132_alt_vol_ctls ; 
 int /*<<< orphan*/  dspio_set_uint_param (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * float_vol_db_lookup ; 

__attribute__((used)) static void ca0132_alt_dsp_volume_put(struct hda_codec *codec, hda_nid_t nid)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int dsp_dir;
	unsigned int lookup_val;

	if (nid == VNID_SPK)
		dsp_dir = DSP_VOL_OUT;
	else
		dsp_dir = DSP_VOL_IN;

	lookup_val = spec->vnode_lvol[nid - VNODE_START_NID];

	dspio_set_uint_param(codec,
		ca0132_alt_vol_ctls[dsp_dir].mid,
		ca0132_alt_vol_ctls[dsp_dir].reqs[0],
		float_vol_db_lookup[lookup_val]);

	lookup_val = spec->vnode_rvol[nid - VNODE_START_NID];

	dspio_set_uint_param(codec,
		ca0132_alt_vol_ctls[dsp_dir].mid,
		ca0132_alt_vol_ctls[dsp_dir].reqs[1],
		float_vol_db_lookup[lookup_val]);

	dspio_set_uint_param(codec,
		ca0132_alt_vol_ctls[dsp_dir].mid,
		ca0132_alt_vol_ctls[dsp_dir].reqs[2], FLOAT_ZERO);
}