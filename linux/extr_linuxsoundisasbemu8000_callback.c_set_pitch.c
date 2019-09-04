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
struct snd_emux_voice {int /*<<< orphan*/  apitch; int /*<<< orphan*/  ch; } ;
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_IP_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_pitch(struct snd_emu8000 *hw, struct snd_emux_voice *vp)
{
	EMU8000_IP_WRITE(hw, vp->ch, vp->apitch);
}