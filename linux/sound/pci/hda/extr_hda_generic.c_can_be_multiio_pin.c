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
 scalar_t__ AC_JACK_PORT_COMPLEX ; 
 unsigned int AC_PINCAP_OUT ; 
 scalar_t__ get_defcfg_connect (unsigned int) ; 
 unsigned int get_defcfg_location (unsigned int) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_query_pin_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool can_be_multiio_pin(struct hda_codec *codec,
			       unsigned int location, hda_nid_t nid)
{
	unsigned int defcfg, caps;

	defcfg = snd_hda_codec_get_pincfg(codec, nid);
	if (get_defcfg_connect(defcfg) != AC_JACK_PORT_COMPLEX)
		return false;
	if (location && get_defcfg_location(defcfg) != location)
		return false;
	caps = snd_hda_query_pin_caps(codec, nid);
	if (!(caps & AC_PINCAP_OUT))
		return false;
	return true;
}