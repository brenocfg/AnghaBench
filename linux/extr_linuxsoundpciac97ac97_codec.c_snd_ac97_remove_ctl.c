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
struct snd_ctl_elem_id {int /*<<< orphan*/  iface; int /*<<< orphan*/  name; } ;
struct snd_ac97 {TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ctl_name (int /*<<< orphan*/ ,char const*,char const*) ; 
 int snd_ctl_remove_id (int /*<<< orphan*/ ,struct snd_ctl_elem_id*) ; 

__attribute__((used)) static int snd_ac97_remove_ctl(struct snd_ac97 *ac97, const char *name,
			       const char *suffix)
{
	struct snd_ctl_elem_id id;
	memset(&id, 0, sizeof(id));
	set_ctl_name(id.name, name, suffix);
	id.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	return snd_ctl_remove_id(ac97->bus->card, &id);
}