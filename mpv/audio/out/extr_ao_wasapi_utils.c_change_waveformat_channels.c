#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_chmap {int /*<<< orphan*/  num; } ;
struct TYPE_5__ {int /*<<< orphan*/  nChannels; } ;
struct TYPE_6__ {int /*<<< orphan*/  dwChannelMask; TYPE_1__ Format; } ;
typedef  TYPE_2__ WAVEFORMATEXTENSIBLE ;

/* Variables and functions */
 int /*<<< orphan*/  mp_chmap_to_waveext (struct mp_chmap*) ; 
 int /*<<< orphan*/  update_waveformat_datarate (TYPE_2__*) ; 

__attribute__((used)) static void change_waveformat_channels(WAVEFORMATEXTENSIBLE *wformat,
                                       struct mp_chmap *channels)
{
    wformat->Format.nChannels = channels->num;
    wformat->dwChannelMask    = mp_chmap_to_waveext(channels);
    update_waveformat_datarate(wformat);
}