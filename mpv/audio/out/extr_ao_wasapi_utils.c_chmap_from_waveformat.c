#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_chmap {scalar_t__ num; } ;
struct TYPE_4__ {int /*<<< orphan*/  dwChannelMask; } ;
typedef  TYPE_1__ WAVEFORMATEXTENSIBLE ;
struct TYPE_5__ {scalar_t__ wFormatTag; scalar_t__ nChannels; } ;
typedef  TYPE_2__ WAVEFORMATEX ;

/* Variables and functions */
 scalar_t__ WAVE_FORMAT_EXTENSIBLE ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  mp_chmap_from_channels (struct mp_chmap*,scalar_t__) ; 
 int /*<<< orphan*/  mp_chmap_from_str (struct mp_chmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_from_waveext (struct mp_chmap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool chmap_from_waveformat(struct mp_chmap *channels,
                                  const WAVEFORMATEX *wf)
{
    if (wf->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
        WAVEFORMATEXTENSIBLE *wformat = (WAVEFORMATEXTENSIBLE *)wf;
        mp_chmap_from_waveext(channels, wformat->dwChannelMask);
    } else {
        mp_chmap_from_channels(channels, wf->nChannels);
    }

    if (channels->num != wf->nChannels) {
        mp_chmap_from_str(channels, bstr0("empty"));
        return false;
    }

    return true;
}