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
struct snd_kcontrol {size_t private_value; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct qtet_kcontrol_private {int /*<<< orphan*/  texts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct qtet_kcontrol_private* qtet_privates ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qtet_enum_info(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_info *uinfo)
{
	struct qtet_kcontrol_private private =
		qtet_privates[kcontrol->private_value];
	return snd_ctl_enum_info(uinfo, 1, ARRAY_SIZE(private.texts),
				 private.texts);
}