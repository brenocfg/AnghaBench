#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nChannels; scalar_t__ rate; scalar_t__ nBits; } ;
struct TYPE_6__ {scalar_t__ nChannels; scalar_t__ nSamplesPerSec; scalar_t__ wBitsPerSample; } ;
typedef  TYPE_1__* LPWAVEFORMATEX ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_4__*) ; 
 TYPE_4__* PCM_Formats ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static DWORD PCM_GetFormatIndex(LPWAVEFORMATEX wfx)
{
    unsigned int i;
    TRACE("(%p)\n", wfx);

    for (i = 0; i < ARRAY_SIZE(PCM_Formats); i++) {
	if (wfx->nChannels == PCM_Formats[i].nChannels &&
	    wfx->nSamplesPerSec == PCM_Formats[i].rate &&
	    wfx->wBitsPerSample == PCM_Formats[i].nBits)
	    return i;
    }
    return 0xFFFFFFFF;
}