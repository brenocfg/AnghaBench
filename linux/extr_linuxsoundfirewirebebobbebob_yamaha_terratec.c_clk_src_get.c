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
struct snd_bebob {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int avc_audio_get_selector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  clk_src_types ; 

__attribute__((used)) static int
clk_src_get(struct snd_bebob *bebob, unsigned int *id)
{
	int err;

	err = avc_audio_get_selector(bebob->unit, 0, 4, id);
	if (err < 0)
		return err;

	if (*id >= ARRAY_SIZE(clk_src_types))
		return -EIO;

	return 0;
}