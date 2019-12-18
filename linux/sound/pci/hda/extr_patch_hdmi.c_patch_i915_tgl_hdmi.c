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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int const*) ; 
 int intel_hsw_common_init (struct hda_codec*,int,int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_i915_tgl_hdmi(struct hda_codec *codec)
{
	/*
	 * pin to port mapping table where the value indicate the pin number and
	 * the index indicate the port number with 1 base.
	 */
	static const int map[] = {0x4, 0x6, 0x8, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};

	return intel_hsw_common_init(codec, 0x02, map, ARRAY_SIZE(map));
}