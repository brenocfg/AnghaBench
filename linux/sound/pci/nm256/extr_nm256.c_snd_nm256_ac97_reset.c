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
struct snd_ac97 {struct nm256* private_data; } ;
struct nm256 {int /*<<< orphan*/  in_resume; int /*<<< orphan*/  reset_workaround_2; int /*<<< orphan*/  reset_workaround; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* nm256_ac97_init_val ; 
 int /*<<< orphan*/  snd_nm256_ac97_write (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_nm256_writeb (struct nm256*,int,int) ; 

__attribute__((used)) static void
snd_nm256_ac97_reset(struct snd_ac97 *ac97)
{
	struct nm256 *chip = ac97->private_data;

	/* Reset the mixer.  'Tis magic!  */
	snd_nm256_writeb(chip, 0x6c0, 1);
	if (! chip->reset_workaround) {
		/* Dell latitude LS will lock up by this */
		snd_nm256_writeb(chip, 0x6cc, 0x87);
	}
	if (! chip->reset_workaround_2) {
		/* Dell latitude CSx will lock up by this */
		snd_nm256_writeb(chip, 0x6cc, 0x80);
		snd_nm256_writeb(chip, 0x6cc, 0x0);
	}
	if (! chip->in_resume) {
		int i;
		for (i = 0; i < ARRAY_SIZE(nm256_ac97_init_val); i++) {
			/* preload the cache, so as to avoid even a single
			 * read of the mixer regs
			 */
			snd_nm256_ac97_write(ac97, nm256_ac97_init_val[i].reg,
					     nm256_ac97_init_val[i].value);
		}
	}
}