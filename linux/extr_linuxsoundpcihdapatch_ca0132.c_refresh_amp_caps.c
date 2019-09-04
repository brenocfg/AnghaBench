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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_AMP_IN_CAP ; 
 int /*<<< orphan*/  AC_PAR_AMP_OUT_CAP ; 
 int HDA_OUTPUT ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int,unsigned int) ; 
 unsigned int snd_hda_param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void refresh_amp_caps(struct hda_codec *codec, hda_nid_t nid, int dir)
{
	unsigned int caps;

	caps = snd_hda_param_read(codec, nid, dir == HDA_OUTPUT ?
				  AC_PAR_AMP_OUT_CAP : AC_PAR_AMP_IN_CAP);
	snd_hda_override_amp_caps(codec, nid, dir, caps);
}