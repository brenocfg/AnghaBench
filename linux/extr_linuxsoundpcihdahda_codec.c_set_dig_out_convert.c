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
 int /*<<< orphan*/  set_dig_out (struct hda_codec*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void set_dig_out_convert(struct hda_codec *codec, hda_nid_t nid,
				       int dig1, int dig2)
{
	unsigned int mask = 0;
	unsigned int val = 0;

	if (dig1 != -1) {
		mask |= 0xff;
		val = dig1;
	}
	if (dig2 != -1) {
		mask |= 0xff00;
		val |= dig2 << 8;
	}
	set_dig_out(codec, nid, mask, val);
}