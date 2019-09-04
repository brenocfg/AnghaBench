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
struct snd_sb {int dummy; } ;

/* Variables and functions */
 unsigned int ENODEV ; 
 int /*<<< orphan*/  SB_DSP_GET_VERSION ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_sbdsp_get_byte (struct snd_sb*) ; 

__attribute__((used)) static int snd_sbdsp_version(struct snd_sb * chip)
{
	unsigned int result = -ENODEV;

	snd_sbdsp_command(chip, SB_DSP_GET_VERSION);
	result = (short) snd_sbdsp_get_byte(chip) << 8;
	result |= (short) snd_sbdsp_get_byte(chip);
	return result;
}