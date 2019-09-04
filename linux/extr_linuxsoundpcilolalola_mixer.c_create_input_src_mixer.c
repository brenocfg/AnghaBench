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
struct lola {int /*<<< orphan*/  card; int /*<<< orphan*/  input_src_caps_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  lola_input_src_mixer ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct lola*) ; 

__attribute__((used)) static int create_input_src_mixer(struct lola *chip)
{
	if (!chip->input_src_caps_mask)
		return 0;

	return snd_ctl_add(chip->card,
			   snd_ctl_new1(&lola_input_src_mixer, chip));
}