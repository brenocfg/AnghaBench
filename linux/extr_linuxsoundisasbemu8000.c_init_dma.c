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
 int /*<<< orphan*/  EMU8000_SMALR_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_SMALW_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_SMARR_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_SMARW_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_dma(struct snd_emu8000 *emu)
{
	EMU8000_SMALR_WRITE(emu, 0);
	EMU8000_SMARR_WRITE(emu, 0);
	EMU8000_SMALW_WRITE(emu, 0);
	EMU8000_SMARW_WRITE(emu, 0);
}