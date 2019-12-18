#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct dvb_frontend_info {int num; int type; int caps; int /*<<< orphan*/  name; struct dtv_property* props; } ;
struct TYPE_3__ {unsigned int len; scalar_t__* data; } ;
struct TYPE_4__ {int data; TYPE_1__ buffer; } ;
struct dtv_property {TYPE_2__ u; int /*<<< orphan*/  cmd; } ;
struct dtv_properties {int num; int type; int caps; int /*<<< orphan*/  name; struct dtv_property* props; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELSYS_IS_SET (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DELSYS_SET (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DTV_API_VERSION ; 
 int /*<<< orphan*/  DTV_ENUM_DELSYS ; 
#define  FE_ATSC 131 
 int FE_CAN_16VSB ; 
 int FE_CAN_2G_MODULATION ; 
 int FE_CAN_8VSB ; 
 int FE_CAN_QAM_256 ; 
 int FE_CAN_QAM_64 ; 
 int FE_CAN_QAM_AUTO ; 
 int FE_CAN_TURBO_FEC ; 
 int /*<<< orphan*/  FE_GET_INFO ; 
 int /*<<< orphan*/  FE_GET_PROPERTY ; 
#define  FE_OFDM 130 
#define  FE_QAM 129 
#define  FE_QPSK 128 
 unsigned int SYS_ATSC ; 
 unsigned int SYS_DVBC_ANNEX_A ; 
 unsigned int SYS_DVBC_ANNEX_B ; 
 unsigned int SYS_DVBC_ANNEX_C ; 
 unsigned int SYS_DVBS ; 
 unsigned int SYS_DVBS2 ; 
 unsigned int SYS_DVBT ; 
 unsigned int SYS_DVBT2 ; 
 unsigned int SYS_DVB__COUNT__ ; 
 unsigned int SYS_TURBO ; 
 int /*<<< orphan*/  errno ; 
 int get_dvb_delsys (unsigned int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct dvb_frontend_info*) ; 
 int /*<<< orphan*/  memset (struct dvb_frontend_info*,int,int) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int,...) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,int,...) ; 

unsigned int dvb_get_tuner_delsys_mask(int fe_fd, struct mp_log *log)
{
    unsigned int ret_mask = 0, delsys;
    struct dtv_property prop[1];
    struct dtv_properties cmdseq = {.num = 1, .props = prop};
    struct dvb_frontend_info fe_info;

#ifdef DVB_USE_S2API
    /* S2API is the DVB API new since 2.6.28.
       It allows to query frontends with multiple delivery systems. */
    mp_verbose(log, "Querying tuner frontend type via DVBv5 API for frontend FD %d\n",
               fe_fd);
    prop[0].cmd = DTV_ENUM_DELSYS;
    if (ioctl(fe_fd, FE_GET_PROPERTY, &cmdseq) < 0) {
        mp_err(log, "DVBv5: FE_GET_PROPERTY(DTV_ENUM_DELSYS) error: %d, FD: %d\n\n", errno, fe_fd);
        goto old_api;
    }
    unsigned int i, delsys_count = prop[0].u.buffer.len;
    mp_verbose(log, "DVBv5: Number of supported delivery systems: %d\n", delsys_count);
    if (delsys_count == 0) {
        mp_err(log, "DVBv5: Frontend FD %d returned no delivery systems!\n", fe_fd);
        goto old_api;
    }
    for (i = 0; i < delsys_count; i++) {
        delsys = (unsigned int)prop[0].u.buffer.data[i];
        DELSYS_SET(ret_mask, delsys);
        mp_verbose(log, "DVBv5: Tuner frontend type seems to be %s\n", get_dvb_delsys(delsys));
    }

    return ret_mask;

old_api:
#endif
    mp_verbose(log, "Querying tuner frontend type via pre-DVBv5 API for frontend FD %d\n",
               fe_fd);

    memset(&fe_info, 0x00, sizeof(struct dvb_frontend_info));
    if (ioctl(fe_fd, FE_GET_INFO, &fe_info) < 0) {
        mp_err(log, "DVBv3: FE_GET_INFO error: %d, FD: %d\n\n", errno, fe_fd);
        return ret_mask;
    }
    /* Try to get kernel DVB API version. */
    prop[0].cmd = DTV_API_VERSION;
    if (ioctl(fe_fd, FE_GET_PROPERTY, &cmdseq) < 0) {
        prop[0].u.data = 0x0300; /* Fail, assume 3.0 */
    }

    mp_verbose(log, "DVBv3: Queried tuner frontend type of device named '%s', FD: %d\n",
               fe_info.name, fe_fd);
    switch (fe_info.type) {
    case FE_OFDM:
        DELSYS_SET(ret_mask, SYS_DVBT);
        if (prop[0].u.data < 0x0500)
            break;
        if (FE_CAN_2G_MODULATION & fe_info.caps) {
            DELSYS_SET(ret_mask, SYS_DVBT2);
        }
        break;
    case FE_QPSK:
        DELSYS_SET(ret_mask, SYS_DVBS);
        if (prop[0].u.data < 0x0500)
            break;
        if (FE_CAN_2G_MODULATION & fe_info.caps) {
            DELSYS_SET(ret_mask, SYS_DVBS2);
        }
#if 0 /* Not used now. */
        if (FE_CAN_TURBO_FEC & fe_info.caps) {
            DELSYS_SET(ret_mask, SYS_TURBO);
        }
#endif
        break;
    case FE_QAM:
        DELSYS_SET(ret_mask, SYS_DVBC_ANNEX_A);
        DELSYS_SET(ret_mask, SYS_DVBC_ANNEX_C);
        break;
#ifdef DVB_ATSC
    case FE_ATSC:
        if ((FE_CAN_8VSB | FE_CAN_16VSB) & fe_info.caps) {
            DELSYS_SET(ret_mask, SYS_ATSC);
        }
        if ((FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_QAM_AUTO) & fe_info.caps) {
            DELSYS_SET(ret_mask, SYS_DVBC_ANNEX_B);
        }
        break;
#endif
    default:
        mp_err(log, "DVBv3: Unknown tuner frontend type: %d\n", fe_info.type);
        return ret_mask;
    }

    for (delsys = 0; delsys < SYS_DVB__COUNT__; delsys ++) {
        if (!DELSYS_IS_SET(ret_mask, delsys))
            continue; /* Skip unsupported. */
        mp_verbose(log, "DVBv3: Tuner frontend type seems to be %s\n", get_dvb_delsys(delsys));
    }

    return ret_mask;
}