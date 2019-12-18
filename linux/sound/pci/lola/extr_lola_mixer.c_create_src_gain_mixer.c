#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lola {int /*<<< orphan*/  card; } ;
struct TYPE_3__ {char* name; int private_value; } ;

/* Variables and functions */
 TYPE_1__ lola_src_gain_mixer ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (TYPE_1__*,struct lola*) ; 

__attribute__((used)) static int create_src_gain_mixer(struct lola *chip,
				 int num, int ofs, char *name)
{
	lola_src_gain_mixer.name = name;
	lola_src_gain_mixer.private_value = ofs + (num << 8);
	return snd_ctl_add(chip->card,
			   snd_ctl_new1(&lola_src_gain_mixer, chip));
}