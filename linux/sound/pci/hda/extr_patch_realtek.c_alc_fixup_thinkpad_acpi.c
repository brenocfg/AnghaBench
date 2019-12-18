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
struct hda_fixup {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_fixup_no_shutup (struct hda_codec*,struct hda_fixup const*,int) ; 
 int /*<<< orphan*/  hda_fixup_thinkpad_acpi (struct hda_codec*,struct hda_fixup const*,int) ; 

__attribute__((used)) static void alc_fixup_thinkpad_acpi(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	alc_fixup_no_shutup(codec, fix, action); /* reduce click noise */
	hda_fixup_thinkpad_acpi(codec, fix, action);
}