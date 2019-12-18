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
typedef  int /*<<< orphan*/  frontend_dev ;
typedef  int /*<<< orphan*/  dvr_dev ;
struct TYPE_6__ {scalar_t__ fe_fd; scalar_t__* demux_fds; scalar_t__ dvr_fd; scalar_t__ demux_fds_cnt; } ;
typedef  TYPE_1__ dvb_state_t ;
struct TYPE_7__ {TYPE_1__* state; } ;
typedef  TYPE_2__ dvb_priv_t ;
typedef  int /*<<< orphan*/  demux_dev ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,...) ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 void* open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,...) ; 

int dvb_open_devices(dvb_priv_t *priv, unsigned int adapter,
    unsigned int frontend, unsigned int demux_cnt)
{
    unsigned int i;
    char frontend_dev[PATH_MAX], dvr_dev[PATH_MAX], demux_dev[PATH_MAX];
    dvb_state_t* state = priv->state;

    snprintf(frontend_dev, sizeof(frontend_dev), "/dev/dvb/adapter%u/frontend%u", adapter, frontend);
    snprintf(dvr_dev, sizeof(dvr_dev), "/dev/dvb/adapter%u/dvr0", adapter);
    snprintf(demux_dev, sizeof(demux_dev), "/dev/dvb/adapter%u/demux0", adapter);
    MP_VERBOSE(priv, "DVB_OPEN_DEVICES: frontend: %s\n", frontend_dev);
    state->fe_fd = open(frontend_dev, O_RDWR | O_NONBLOCK | O_CLOEXEC);
    if (state->fe_fd < 0) {
        MP_ERR(priv, "ERROR OPENING FRONTEND DEVICE %s: ERRNO %d\n",
               frontend_dev, errno);
        return 0;
    }
    state->demux_fds_cnt = 0;
    MP_VERBOSE(priv, "DVB_OPEN_DEVICES(%d)\n", demux_cnt);
    for (i = 0; i < demux_cnt; i++) {
        state->demux_fds[i] = open(demux_dev, O_RDWR | O_NONBLOCK | O_CLOEXEC);
        if (state->demux_fds[i] < 0) {
            MP_ERR(priv, "ERROR OPENING DEMUX 0: %d\n", errno);
            return 0;
        } else {
            MP_VERBOSE(priv, "OPEN(%d), file %s: FD=%d, CNT=%d\n", i, demux_dev,
                       state->demux_fds[i], state->demux_fds_cnt);
            state->demux_fds_cnt++;
        }
    }

    state->dvr_fd = open(dvr_dev, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
    if (state->dvr_fd < 0) {
        MP_ERR(priv, "ERROR OPENING DVR DEVICE %s: %d\n", dvr_dev, errno);
        return 0;
    }

    return 1;
}