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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PSND_MIXER ;

/* Variables and functions */
 int /*<<< orphan*/  ClearMixerCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SndMixerClose (int /*<<< orphan*/ ) ; 

VOID
SndMixerDestroy(PSND_MIXER Mixer)
{
    ClearMixerCache(Mixer);
    SndMixerClose(Mixer);
    HeapFree(GetProcessHeap(),
             0,
             Mixer);
}