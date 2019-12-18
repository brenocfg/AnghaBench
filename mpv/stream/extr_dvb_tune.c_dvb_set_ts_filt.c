#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct dmx_pes_filter_params {int /*<<< orphan*/  flags; int /*<<< orphan*/  pes_type; int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  dvb_priv_t ;
typedef  int /*<<< orphan*/  dmx_pes_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_IMMEDIATE_START ; 
 int /*<<< orphan*/  DMX_IN_FRONTEND ; 
 int /*<<< orphan*/  DMX_OUT_TS_TAP ; 
 int /*<<< orphan*/  DMX_SET_BUFFER_SIZE ; 
 int /*<<< orphan*/  DMX_SET_PES_FILTER ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 

int dvb_set_ts_filt(dvb_priv_t *priv, int fd, uint16_t pid,
                    dmx_pes_type_t pestype)
{
    int i;
    struct dmx_pes_filter_params pesFilterParams;

    pesFilterParams.pid     = pid;
    pesFilterParams.input   = DMX_IN_FRONTEND;
    pesFilterParams.output  = DMX_OUT_TS_TAP;
    pesFilterParams.pes_type = pestype;
    pesFilterParams.flags   = DMX_IMMEDIATE_START;

    {
        int buffersize = 256 * 1024;
        if (ioctl(fd, DMX_SET_BUFFER_SIZE, buffersize) < 0)
            MP_ERR(priv, "ERROR IN DMX_SET_BUFFER_SIZE %i for fd %d: ERRNO: %d\n",
                   pid, fd, errno);
    }

    errno = 0;
    if ((i = ioctl(fd, DMX_SET_PES_FILTER, &pesFilterParams)) < 0) {
        MP_ERR(priv, "ERROR IN SETTING DMX_FILTER %i for fd %d: ERRNO: %d\n",
               pid, fd, errno);
        return 0;
    }

    MP_VERBOSE(priv, "SET PES FILTER ON PID %d to fd %d, RESULT: %d, ERRNO: %d\n",
               pid, fd, i, errno);
    return 1;
}