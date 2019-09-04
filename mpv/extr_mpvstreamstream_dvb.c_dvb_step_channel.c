#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* priv; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_12__ {size_t cur_adapter; TYPE_1__* adapters; } ;
typedef  TYPE_3__ dvb_state_t ;
struct TYPE_13__ {TYPE_3__* state; } ;
typedef  TYPE_4__ dvb_priv_t ;
struct TYPE_14__ {int NUM_CHANNELS; int current; } ;
typedef  TYPE_5__ dvb_channels_list_t ;
struct TYPE_10__ {TYPE_5__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,int) ; 
 int dvb_set_channel (TYPE_2__*,size_t,unsigned int) ; 

int dvb_step_channel(stream_t *stream, int dir)
{
    unsigned int new_current;
    dvb_priv_t *priv = stream->priv;
    dvb_state_t *state = priv->state;
    dvb_channels_list_t *list = state->adapters[state->cur_adapter].list;

    MP_VERBOSE(stream, "DVB_STEP_CHANNEL dir %d\n", dir);

    if (list == NULL) {
        MP_ERR(stream, "dvb_step_channel: NULL list_ptr, quit\n");
        return 0;
    }

    new_current = (list->NUM_CHANNELS + list->current +
                  (dir >= 0 ? 1 : -1)) % list->NUM_CHANNELS;

    return dvb_set_channel(stream, state->cur_adapter, new_current);
}