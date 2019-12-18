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
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
struct TYPE_3__ {scalar_t__ wFormatTag; int cbSize; } ;
typedef  TYPE_1__* LPCWAVEFORMATEX ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ WAVE_FORMAT_PCM ; 

__attribute__((used)) static DWORD DSOUND_GetFormatSize(LPCWAVEFORMATEX wfex)
{
	if (wfex->wFormatTag == WAVE_FORMAT_PCM)
		return sizeof(WAVEFORMATEX);
	else
		return sizeof(WAVEFORMATEX) + wfex->cbSize;
}