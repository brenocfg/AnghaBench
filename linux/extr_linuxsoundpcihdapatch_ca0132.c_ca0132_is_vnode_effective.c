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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int shared_out_nid; int shared_mic_nid; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
#define  VNID_MIC 129 
#define  VNID_SPK 128 

__attribute__((used)) static bool ca0132_is_vnode_effective(struct hda_codec *codec,
				     hda_nid_t vnid,
				     hda_nid_t *shared_nid)
{
	struct ca0132_spec *spec = codec->spec;
	hda_nid_t nid;

	switch (vnid) {
	case VNID_SPK:
		nid = spec->shared_out_nid;
		break;
	case VNID_MIC:
		nid = spec->shared_mic_nid;
		break;
	default:
		return false;
	}

	if (shared_nid)
		*shared_nid = nid;

	return true;
}