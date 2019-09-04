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
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int EMU8000_SMALW_READ (struct snd_emu8000*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snd_emu8000_write_wait(struct snd_emu8000 *emu)
{
	while ((EMU8000_SMALW_READ(emu) & 0x80000000) != 0) {
		schedule_timeout_interruptible(1);
		if (signal_pending(current))
			break;
	}
}