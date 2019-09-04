#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wasapi_state {int /*<<< orphan*/  opt_exclusive; } ;
struct mp_chmap_sel {struct wasapi_state* tmp; } ;
struct mp_chmap {int dummy; } ;
struct ao {struct mp_chmap channels; struct wasapi_state* priv; } ;
struct TYPE_7__ {scalar_t__ nSamplesPerSec; } ;
struct TYPE_8__ {TYPE_1__ Format; } ;
typedef  TYPE_2__ WAVEFORMATEXTENSIBLE ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct ao*,char*) ; 
 scalar_t__ ao_chmap_sel_adjust2 (struct ao*,struct mp_chmap_sel*,struct mp_chmap*,int) ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  change_waveformat_channels (TYPE_2__*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_from_str (struct mp_chmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_map (struct mp_chmap_sel*,struct mp_chmap*) ; 
 scalar_t__ search_samplerates (struct ao*,TYPE_2__*,struct mp_chmap*) ; 
 scalar_t__ try_format_exclusive (struct ao*,TYPE_2__*) ; 

__attribute__((used)) static bool search_channels(struct ao *ao, WAVEFORMATEXTENSIBLE *wformat)
{
    struct wasapi_state *state = ao->priv;
    struct mp_chmap_sel chmap_sel = {.tmp = state};
    struct mp_chmap entry;
    // put common layouts first so that we find sample rate/format early
    char *channel_layouts[] =
        {"stereo", "5.1", "7.1", "6.1", "mono", "2.1", "4.0", "5.0",
         "3.0", "3.0(back)",
         "quad", "quad(side)", "3.1",
         "5.0(side)", "4.1",
         "5.1(side)", "6.0", "6.0(front)", "hexagonal"
         "6.1(back)", "6.1(front)", "7.0", "7.0(front)",
         "7.1(wide)", "7.1(wide-side)", "7.1(rear)", "octagonal", NULL};

    wformat->Format.nSamplesPerSec = 0;
    for (int j = 0; channel_layouts[j]; j++) {
        mp_chmap_from_str(&entry, bstr0(channel_layouts[j]));
        if (!wformat->Format.nSamplesPerSec) {
            if (search_samplerates(ao, wformat, &entry))
                mp_chmap_sel_add_map(&chmap_sel, &entry);
        } else {
            change_waveformat_channels(wformat, &entry);
            if (try_format_exclusive(ao, wformat))
                mp_chmap_sel_add_map(&chmap_sel, &entry);
        }
    }

    entry = ao->channels;
    if (ao_chmap_sel_adjust2(ao, &chmap_sel, &entry, !state->opt_exclusive)){
        change_waveformat_channels(wformat, &entry);
        return true;
    }

    MP_ERR(ao, "No suitable audio format found\n");
    return false;
}