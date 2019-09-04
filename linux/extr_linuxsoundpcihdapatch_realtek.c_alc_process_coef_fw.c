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
struct coef_fw {unsigned short mask; int /*<<< orphan*/  val; int /*<<< orphan*/  idx; scalar_t__ nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_update_coefex_idx (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alc_write_coefex_idx (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_process_coef_fw(struct hda_codec *codec,
				const struct coef_fw *fw)
{
	for (; fw->nid; fw++) {
		if (fw->mask == (unsigned short)-1)
			alc_write_coefex_idx(codec, fw->nid, fw->idx, fw->val);
		else
			alc_update_coefex_idx(codec, fw->nid, fw->idx,
					      fw->mask, fw->val);
	}
}