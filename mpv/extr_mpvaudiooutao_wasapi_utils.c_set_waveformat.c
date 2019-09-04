#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wasapi_sample_fmt {int /*<<< orphan*/  used_msb; int /*<<< orphan*/  mp_format; int /*<<< orphan*/  bits; } ;
struct mp_chmap {int /*<<< orphan*/  num; } ;
struct TYPE_6__ {int /*<<< orphan*/  wValidBitsPerSample; } ;
struct TYPE_7__ {int cbSize; int /*<<< orphan*/  wBitsPerSample; int /*<<< orphan*/  nSamplesPerSec; int /*<<< orphan*/  nChannels; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwChannelMask; TYPE_1__ Samples; int /*<<< orphan*/  SubFormat; TYPE_2__ Format; } ;
typedef  TYPE_3__ WAVEFORMATEXTENSIBLE ;
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WAVE_FORMAT_EXTENSIBLE ; 
 int /*<<< orphan*/ * format_to_subtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_to_waveext (struct mp_chmap*) ; 
 int /*<<< orphan*/  update_waveformat_datarate (TYPE_3__*) ; 

__attribute__((used)) static void set_waveformat(WAVEFORMATEXTENSIBLE *wformat,
                           struct wasapi_sample_fmt *format,
                           DWORD samplerate, struct mp_chmap *channels)
{
    wformat->Format.wFormatTag     = WAVE_FORMAT_EXTENSIBLE;
    wformat->Format.nChannels      = channels->num;
    wformat->Format.nSamplesPerSec = samplerate;
    wformat->Format.wBitsPerSample = format->bits;
    wformat->Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);

    wformat->SubFormat                   = *format_to_subtype(format->mp_format);
    wformat->Samples.wValidBitsPerSample = format->used_msb;
    wformat->dwChannelMask               = mp_chmap_to_waveext(channels);
    update_waveformat_datarate(wformat);
}