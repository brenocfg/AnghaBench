#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ priv; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_9__ {int switching_channel; } ;
typedef  TYPE_2__ dvb_state_t ;
struct TYPE_10__ {int /*<<< orphan*/  prog; TYPE_2__* state; int /*<<< orphan*/  opts_cache; } ;
typedef  TYPE_3__ dvb_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dvb_parse_path (TYPE_1__*) ; 
 int dvb_streaming_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ m_config_cache_update (int /*<<< orphan*/ ) ; 
 int mp_time_sec () ; 

void dvb_update_config(stream_t *stream)
{
    static int last_check = 0;
    int now = (int)(mp_time_sec()*10);

    // Throttle the check to at maximum once every 0.1 s.
    if (now != last_check) {
        last_check = now;
        dvb_priv_t *priv  = (dvb_priv_t *) stream->priv;
        if (m_config_cache_update(priv->opts_cache)) {
            dvb_state_t *state = priv->state;

            // Re-parse stream path, if we have cfg parameters now,
            // these should be preferred.
            if (!dvb_parse_path(stream)) {
                MP_ERR(stream, "error parsing DVB config, not tuning.");
                return;
            }

            int r = dvb_streaming_start(stream, priv->prog);
            if (r) {
                // Stream will be pulled down after channel switch,
                // persist state.
                state->switching_channel = true;
            }
        }
    }
}