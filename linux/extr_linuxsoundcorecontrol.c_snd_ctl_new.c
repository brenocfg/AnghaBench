#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol_volatile {int dummy; } ;
struct snd_kcontrol {unsigned int count; TYPE_1__* vd; } ;
struct snd_ctl_file {int dummy; } ;
struct TYPE_2__ {unsigned int access; struct snd_ctl_file* owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAX_CONTROL_COUNT ; 
 struct snd_kcontrol* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ctl_new(struct snd_kcontrol **kctl, unsigned int count,
		       unsigned int access, struct snd_ctl_file *file)
{
	unsigned int size;
	unsigned int idx;

	if (count == 0 || count > MAX_CONTROL_COUNT)
		return -EINVAL;

	size  = sizeof(struct snd_kcontrol);
	size += sizeof(struct snd_kcontrol_volatile) * count;

	*kctl = kzalloc(size, GFP_KERNEL);
	if (!*kctl)
		return -ENOMEM;

	for (idx = 0; idx < count; idx++) {
		(*kctl)->vd[idx].access = access;
		(*kctl)->vd[idx].owner = file;
	}
	(*kctl)->count = count;

	return 0;
}