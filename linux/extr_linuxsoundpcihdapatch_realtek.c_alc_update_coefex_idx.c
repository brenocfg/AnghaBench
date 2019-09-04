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
 unsigned int alc_read_coefex_idx (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  alc_write_coefex_idx (struct hda_codec*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void alc_update_coefex_idx(struct hda_codec *codec, hda_nid_t nid,
				  unsigned int coef_idx, unsigned int mask,
				  unsigned int bits_set)
{
	unsigned int val = alc_read_coefex_idx(codec, nid, coef_idx);

	if (val != -1)
		alc_write_coefex_idx(codec, nid, coef_idx,
				     (val & ~mask) | bits_set);
}