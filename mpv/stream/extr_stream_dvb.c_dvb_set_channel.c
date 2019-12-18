#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_5__* priv; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_22__ {unsigned int adapters_count; int is_on; int retry; unsigned int cur_adapter; scalar_t__ cur_frontend; scalar_t__ last_freq; int /*<<< orphan*/ * demux_fds; TYPE_1__* adapters; } ;
typedef  TYPE_4__ dvb_state_t ;
struct TYPE_23__ {TYPE_2__* opts; scalar_t__ state; } ;
typedef  TYPE_5__ dvb_priv_t ;
struct TYPE_24__ {unsigned int NUM_CHANNELS; unsigned int current; TYPE_7__* channels; } ;
typedef  TYPE_6__ dvb_channels_list_t ;
struct TYPE_25__ {scalar_t__ frontend; int pids_cnt; scalar_t__ freq; int service_id; int* pids; int /*<<< orphan*/  hier; int /*<<< orphan*/  cr_lp; int /*<<< orphan*/  cr; int /*<<< orphan*/  bw; int /*<<< orphan*/  trans; int /*<<< orphan*/  gi; int /*<<< orphan*/  mod; int /*<<< orphan*/  inv; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  diseqc; int /*<<< orphan*/  srate; int /*<<< orphan*/  pol; int /*<<< orphan*/  delsys; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ dvb_channel_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_20__ {int /*<<< orphan*/  cfg_timeout; } ;
struct TYPE_19__ {int devno; TYPE_6__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_PES_OTHER ; 
 int /*<<< orphan*/  MP_ERR (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_3__*,char*,int,...) ; 
 int /*<<< orphan*/  dvb_fix_demuxes (TYPE_5__*,int) ; 
 int dvb_get_pmt_pid (TYPE_5__*,unsigned int,int) ; 
 int /*<<< orphan*/  dvb_open_devices (TYPE_5__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  dvb_set_ts_filt (TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dvb_streaming_read (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dvb_tune (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbin_close (TYPE_3__*) ; 
 int /*<<< orphan*/  stream_drop_buffers (TYPE_3__*) ; 

int dvb_set_channel(stream_t *stream, unsigned int adapter, unsigned int n)
{
    dvb_channels_list_t *new_list;
    dvb_channel_t *channel;
    dvb_priv_t *priv = stream->priv;
    char buf[4096];
    dvb_state_t *state = (dvb_state_t *) priv->state;
    int devno;
    int i;

    if (adapter >= state->adapters_count) {
        MP_ERR(stream, "dvb_set_channel: INVALID internal ADAPTER NUMBER: %d vs %d, abort\n",
               adapter, state->adapters_count);
        return 0;
    }

    devno = state->adapters[adapter].devno;
    new_list = state->adapters[adapter].list;
    if (n > new_list->NUM_CHANNELS) {
        MP_ERR(stream, "dvb_set_channel: INVALID CHANNEL NUMBER: %d, for "
               "adapter %d, abort\n", n, devno);
        return 0;
    }
    channel = &(new_list->channels[n]);

    if (state->is_on) {  //the fds are already open and we have to stop the demuxers
        /* Remove all demuxes. */
        dvb_fix_demuxes(priv, 0);

        state->retry = 0;
        //empty both the stream's and driver's buffer
        while (dvb_streaming_read(stream, buf, sizeof(buf)) > 0) {}
        if (state->cur_adapter != adapter ||
            state->cur_frontend != channel->frontend) {
            dvbin_close(stream);
            if (!dvb_open_devices(priv, devno, channel->frontend, channel->pids_cnt)) {
                MP_ERR(stream, "DVB_SET_CHANNEL, COULDN'T OPEN DEVICES OF "
                       "ADAPTER: %d, EXIT\n", devno);
                return 0;
            }
        } else {
            // close all demux_fds with pos > pids required for the new channel
            // or open other demux_fds if we have too few
            if (!dvb_fix_demuxes(priv, channel->pids_cnt))
                return 0;
        }
    } else {
        if (!dvb_open_devices(priv, devno, channel->frontend, channel->pids_cnt)) {
            MP_ERR(stream, "DVB_SET_CHANNEL2, COULDN'T OPEN DEVICES OF "
                   "ADAPTER: %d, EXIT\n", devno);
            return 0;
        }
    }

    state->retry = 5;
    new_list->current = n;
    MP_VERBOSE(stream, "DVB_SET_CHANNEL: new channel name=%s, adapter: %d, "
               "channel %d\n", channel->name, devno, n);

    stream_drop_buffers(stream);

    if (channel->freq != state->last_freq) {
        if (!dvb_tune(priv, channel->delsys, channel->freq,
                      channel->pol, channel->srate, channel->diseqc,
                      channel->stream_id, channel->inv,
                      channel->mod, channel->gi,
                      channel->trans, channel->bw, channel->cr, channel->cr_lp,
                      channel->hier, priv->opts->cfg_timeout))
            return 0;
    }

    state->is_on = 1;
    state->last_freq = channel->freq;
    state->cur_adapter = adapter;
    state->cur_frontend = channel->frontend;

    if (channel->service_id != -1) {
        /* We need the PMT-PID in addition.
           If it has not yet beem resolved, do it now. */
        for (i = 0; i < channel->pids_cnt; i++) {
            if (channel->pids[i] == -1) {
                MP_VERBOSE(stream, "DVB_SET_CHANNEL: PMT-PID for service %d "
                           "not resolved yet, parsing PAT...\n",
                           channel->service_id);
                int pmt_pid = dvb_get_pmt_pid(priv, adapter, channel->service_id);
                MP_VERBOSE(stream, "DVB_SET_CHANNEL: Found PMT-PID: %d\n",
                           pmt_pid);
                channel->pids[i] = pmt_pid;
            }
        }
    }

    // sets demux filters and restart the stream
    for (i = 0; i < channel->pids_cnt; i++) {
        if (channel->pids[i] == -1) {
            // In case PMT was not resolved, skip it here.
            MP_ERR(stream, "DVB_SET_CHANNEL: PMT-PID not found, "
                           "teletext-decoding may fail.\n");
        } else {
            if (!dvb_set_ts_filt(priv, state->demux_fds[i], channel->pids[i],
                                 DMX_PES_OTHER))
                return 0;
        }
    }

    return 1;
}