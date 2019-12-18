#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wasapi_sample_fmt {int bits; int used_msb; int /*<<< orphan*/ * subtype; scalar_t__ mp_format; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int wValidBitsPerSample; } ;
struct TYPE_6__ {TYPE_1__ Samples; int /*<<< orphan*/  SubFormat; } ;
typedef  TYPE_2__ WAVEFORMATEXTENSIBLE ;
struct TYPE_7__ {int wBitsPerSample; int wFormatTag; } ;
typedef  TYPE_3__ WAVEFORMATEX ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
#define  WAVE_FORMAT_EXTENSIBLE 130 
#define  WAVE_FORMAT_IEEE_FLOAT 129 
#define  WAVE_FORMAT_PCM 128 
 struct wasapi_sample_fmt* wasapi_formats ; 

__attribute__((used)) static struct wasapi_sample_fmt format_from_waveformat(WAVEFORMATEX *wf)
{
    struct wasapi_sample_fmt res = {0};

    for (int n = 0; wasapi_formats[n].mp_format; n++) {
        const struct wasapi_sample_fmt *fmt = &wasapi_formats[n];
        int valid_bits = 0;

        if (wf->wBitsPerSample != fmt->bits)
            continue;

        const GUID *wf_guid = NULL;

        switch (wf->wFormatTag) {
        case WAVE_FORMAT_EXTENSIBLE: {
            WAVEFORMATEXTENSIBLE *wformat = (WAVEFORMATEXTENSIBLE *)wf;
            wf_guid = &wformat->SubFormat;
            if (IsEqualGUID(wf_guid, &KSDATAFORMAT_SUBTYPE_PCM))
                valid_bits = wformat->Samples.wValidBitsPerSample;
            break;
        }
        case WAVE_FORMAT_PCM:
            wf_guid = &KSDATAFORMAT_SUBTYPE_PCM;
            break;
        case WAVE_FORMAT_IEEE_FLOAT:
            wf_guid = &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
            break;
        }

        if (!wf_guid || !IsEqualGUID(wf_guid, fmt->subtype))
            continue;

        res = *fmt;
        if (valid_bits > 0 && valid_bits < fmt->bits)
            res.used_msb = valid_bits;
        break;
    }

    return res;
}