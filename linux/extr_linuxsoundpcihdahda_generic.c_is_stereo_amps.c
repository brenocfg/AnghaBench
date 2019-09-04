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
 unsigned int AC_WCAP_STEREO ; 
 scalar_t__ AC_WID_AUD_MIX ; 
 int HDA_INPUT ; 
 unsigned int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_wcaps_type (unsigned int) ; 
 scalar_t__ snd_hda_get_connections (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_hda_get_num_conns (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_stereo_amps(struct hda_codec *codec, hda_nid_t nid, int dir)
{
	unsigned int wcaps = get_wcaps(codec, nid);
	hda_nid_t conn;

	if (wcaps & AC_WCAP_STEREO)
		return true;
	if (dir != HDA_INPUT || get_wcaps_type(wcaps) != AC_WID_AUD_MIX)
		return false;
	if (snd_hda_get_num_conns(codec, nid) != 1)
		return false;
	if (snd_hda_get_connections(codec, nid, &conn, 1) < 0)
		return false;
	return !!(get_wcaps(codec, conn) & AC_WCAP_STEREO);
}