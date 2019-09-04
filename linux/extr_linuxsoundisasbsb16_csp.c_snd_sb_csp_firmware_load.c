#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_sb_csp {struct firmware const** csp_programs; TYPE_2__* chip; } ;
typedef  struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } const firmware ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const* const*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ CSP_PROGRAM_COUNT ; 
 int request_firmware (struct firmware const**,char const* const,int /*<<< orphan*/ ) ; 
 int snd_sb_csp_load (struct snd_sb_csp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_sb_csp_firmware_load(struct snd_sb_csp *p, int index, int flags)
{
	static const char *const names[] = {
		"sb16/mulaw_main.csp",
		"sb16/alaw_main.csp",
		"sb16/ima_adpcm_init.csp",
		"sb16/ima_adpcm_playback.csp",
		"sb16/ima_adpcm_capture.csp",
	};
	const struct firmware *program;

	BUILD_BUG_ON(ARRAY_SIZE(names) != CSP_PROGRAM_COUNT);
	program = p->csp_programs[index];
	if (!program) {
		int err = request_firmware(&program, names[index],
				       p->chip->card->dev);
		if (err < 0)
			return err;
		p->csp_programs[index] = program;
	}
	return snd_sb_csp_load(p, program->data, program->size, flags);
}