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
struct user_element {unsigned int elem_data_size; char* elem_data; } ;
struct snd_kcontrol {struct user_element* private_data; } ;
struct snd_ctl_elem_value {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned int snd_ctl_get_ioff (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ctl_elem_user_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct user_element *ue = kcontrol->private_data;
	unsigned int size = ue->elem_data_size;
	char *src = ue->elem_data +
			snd_ctl_get_ioff(kcontrol, &ucontrol->id) * size;

	memcpy(&ucontrol->value, src, size);
	return 0;
}