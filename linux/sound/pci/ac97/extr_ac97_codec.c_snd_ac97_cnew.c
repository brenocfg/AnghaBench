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
typedef  int /*<<< orphan*/  template ;
struct snd_kcontrol_new {int /*<<< orphan*/  index; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_ac97 {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct snd_kcontrol_new*,struct snd_kcontrol_new const*,int) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_ac97*) ; 

__attribute__((used)) static struct snd_kcontrol *snd_ac97_cnew(const struct snd_kcontrol_new *_template,
					  struct snd_ac97 * ac97)
{
	struct snd_kcontrol_new template;
	memcpy(&template, _template, sizeof(template));
	template.index = ac97->num;
	return snd_ctl_new1(&template, ac97);
}