#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int streaming; char* demuxer; char* lavf_type; int extended_ctrls; TYPE_6__* priv; int /*<<< orphan*/  control; int /*<<< orphan*/  close; int /*<<< orphan*/  fill_buffer; int /*<<< orphan*/  log; int /*<<< orphan*/  global; } ;
typedef  TYPE_4__ stream_t ;
struct TYPE_22__ {int stream_used; int is_on; int cur_adapter; int cur_frontend; int adapters_count; TYPE_3__* adapters; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_5__ dvb_state_t ;
struct TYPE_23__ {scalar_t__ cfg_devno; scalar_t__* cfg_prog; int /*<<< orphan*/  cfg_timeout; int /*<<< orphan*/  log; TYPE_5__* state; } ;
typedef  TYPE_6__ dvb_priv_t ;
struct TYPE_20__ {scalar_t__ devno; TYPE_2__* list; } ;
struct TYPE_19__ {TYPE_1__* channels; } ;
struct TYPE_18__ {char* name; } ;
struct TYPE_17__ {scalar_t__ stream_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_4__*,char*,scalar_t__*,scalar_t__) ; 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
 TYPE_5__* dvb_get_state (TYPE_4__*) ; 
 int /*<<< orphan*/  dvb_streaming_read ; 
 int /*<<< orphan*/  dvb_streaming_start (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dvbin_close ; 
 int /*<<< orphan*/  dvbin_stream_control ; 
 TYPE_10__* global_dvb_state ; 
 int /*<<< orphan*/  global_dvb_state_lock ; 
 TYPE_6__* mp_get_config_group (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_dvb_conf ; 
 int /*<<< orphan*/  talloc_free (TYPE_6__*) ; 

__attribute__((used)) static int dvb_open(stream_t *stream)
{
    // I don't force  the file format because, although it's almost always TS,
    // there are some providers that stream an IP multicast with M$ Mpeg4 inside
    dvb_priv_t *priv = NULL;
    char *progname;
    int i;

    pthread_mutex_lock(&global_dvb_state_lock);
    if (global_dvb_state && global_dvb_state->stream_used) {
      MP_ERR(stream, "DVB stream already in use, only one DVB stream can exist at a time!\n");
      pthread_mutex_unlock(&global_dvb_state_lock);
      goto err_out;
    }

    // Need to re-get config in any case, not part of global state.
    stream->priv = mp_get_config_group(stream, stream->global, &stream_dvb_conf);
    dvb_state_t *state = dvb_get_state(stream);

    priv = stream->priv;
    priv->state = state;
    priv->log = stream->log;
    if (state == NULL) {
        MP_ERR(stream, "DVB CONFIGURATION IS EMPTY, exit\n");
        pthread_mutex_unlock(&global_dvb_state_lock);
        goto err_out;
    }
    state->stream_used = true;
    pthread_mutex_unlock(&global_dvb_state_lock);

    if (state->is_on != 1) {
      // State could be already initialized, for example, we just did a channel switch.
      // The following setup only has to be done once.

      state->cur_adapter = -1;
      state->cur_frontend = -1;
      for (i = 0; i < state->adapters_count; i++) {
          if (state->adapters[i].devno == priv->cfg_devno) {
              state->cur_adapter = i;
              break;
          }
      }

      if (state->cur_adapter == -1) {
          MP_ERR(stream, "NO CONFIGURATION FOUND FOR ADAPTER N. %d, exit\n",
                 priv->cfg_devno);
          goto err_out;
      }
      state->timeout = priv->cfg_timeout;

      MP_VERBOSE(stream, "OPEN_DVB: prog=%s, devno=%d\n",
                 priv->cfg_prog, state->adapters[state->cur_adapter].devno);

      if ((priv->cfg_prog == NULL || priv->cfg_prog[0] == 0) &&
          state->adapters[state->cur_adapter].list != NULL) {
          progname = state->adapters[state->cur_adapter].list->channels[0].name;
      } else {
          progname = priv->cfg_prog;
      }

      if (!dvb_streaming_start(stream, progname))
          goto err_out;
    }

    stream->fill_buffer = dvb_streaming_read;
    stream->close = dvbin_close;
    stream->control = dvbin_stream_control;
    stream->streaming = true;
    stream->demuxer = "lavf";
    stream->lavf_type = "mpegts";
    stream->extended_ctrls = true;

    return STREAM_OK;

err_out:
    talloc_free(priv);
    stream->priv = NULL;
    return STREAM_ERROR;
}