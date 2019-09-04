#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* priv; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_14__ {size_t cur_adapter; TYPE_1__* adapters; scalar_t__ is_on; } ;
typedef  TYPE_3__ dvb_state_t ;
struct TYPE_15__ {int /*<<< orphan*/  cfg_devno; TYPE_3__* state; } ;
typedef  TYPE_4__ dvb_priv_t ;
struct TYPE_16__ {int NUM_CHANNELS; int current; TYPE_6__* channels; } ;
typedef  TYPE_5__ dvb_channels_list_t ;
struct TYPE_17__ {int /*<<< orphan*/  freq; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ dvb_channel_t ;
struct TYPE_12__ {TYPE_5__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dvb_set_channel (TYPE_2__*,size_t,int) ; 
 int /*<<< orphan*/  dvbin_close (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dvb_streaming_start(stream_t *stream, char *progname)
{
    int i;
    dvb_channel_t *channel = NULL;
    dvb_priv_t *priv = stream->priv;
    dvb_state_t *state = priv->state;
    dvb_channels_list_t *list;

    if (progname == NULL)
        return 0;
    MP_VERBOSE(stream, "\r\ndvb_streaming_start(PROG: %s, ADAPTER: %d)\n",
               progname, priv->cfg_devno);

    state->is_on = 0;
    list = state->adapters[state->cur_adapter].list;
    for (i = 0; i < list->NUM_CHANNELS; i ++) {
        if (!strcmp(list->channels[i].name, progname)) {
            channel = &(list->channels[i]);
            break;
        }
    }

    if (channel == NULL) {
        MP_ERR(stream, "\n\nDVBIN: no such channel \"%s\"\n\n", progname);
        return 0;
    }

    list->current = i;
    MP_VERBOSE(stream, "PROGRAM NUMBER %d: name=%s, freq=%u\n", i,
               channel->name, channel->freq);

    if (!dvb_set_channel(stream, state->cur_adapter, list->current)) {
        MP_ERR(stream, "ERROR, COULDN'T SET CHANNEL  %i: \"%s\"\n", list->current, progname);
        dvbin_close(stream);
        return 0;
    }

    MP_VERBOSE(stream, "SUCCESSFUL EXIT from dvb_streaming_start\n");

    return 1;
}