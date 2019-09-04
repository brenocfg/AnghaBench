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
 int /*<<< orphan*/  VIAHDMI_CVT_NID ; 
 int /*<<< orphan*/  VIAHDMI_PIN_NID ; 
 int patch_simple_hdmi (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_via_hdmi(struct hda_codec *codec)
{
	return patch_simple_hdmi(codec, VIAHDMI_CVT_NID, VIAHDMI_PIN_NID);
}