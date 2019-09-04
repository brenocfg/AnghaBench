#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wasapi_sample_fmt {scalar_t__ mp_format; } ;
struct mp_chmap {int dummy; } ;
struct ao {int /*<<< orphan*/  format; } ;
struct TYPE_6__ {scalar_t__ wBitsPerSample; } ;
struct TYPE_7__ {TYPE_1__ Format; } ;
typedef  TYPE_2__ WAVEFORMATEXTENSIBLE ;

/* Variables and functions */
 int MP_ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_waveformat (TYPE_2__*,struct wasapi_sample_fmt*,int,struct mp_chmap*) ; 
 scalar_t__ try_format_exclusive (struct ao*,TYPE_2__*) ; 
 int /*<<< orphan*/  wasapi_formats ; 
 int /*<<< orphan*/  wasapi_get_best_sample_formats (int /*<<< orphan*/ ,struct wasapi_sample_fmt*) ; 

__attribute__((used)) static bool search_sample_formats(struct ao *ao, WAVEFORMATEXTENSIBLE *wformat,
                                  int samplerate, struct mp_chmap *channels)
{
    struct wasapi_sample_fmt alt_formats[MP_ARRAY_SIZE(wasapi_formats)];
    wasapi_get_best_sample_formats(ao->format, alt_formats);
    for (int n = 0; alt_formats[n].mp_format; n++) {
        set_waveformat(wformat, &alt_formats[n], samplerate, channels);
        if (try_format_exclusive(ao, wformat))
            return true;
    }

    wformat->Format.wBitsPerSample = 0;
    return false;
}