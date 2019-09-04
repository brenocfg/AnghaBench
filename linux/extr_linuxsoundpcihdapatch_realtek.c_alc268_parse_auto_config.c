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
typedef  int hda_nid_t ;

/* Variables and functions */
 int alc_parse_auto_config (struct hda_codec*,int /*<<< orphan*/ *,int const*) ; 

__attribute__((used)) static int alc268_parse_auto_config(struct hda_codec *codec)
{
	static const hda_nid_t alc268_ssids[] = { 0x15, 0x1b, 0x14, 0 };
	return alc_parse_auto_config(codec, NULL, alc268_ssids);
}