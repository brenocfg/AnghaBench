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
 int /*<<< orphan*/  alc668_coefs ; 
 int /*<<< orphan*/  alc_process_coef_fw (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc668_restore_default_value(struct hda_codec *codec)
{
	alc_process_coef_fw(codec, alc668_coefs);
}