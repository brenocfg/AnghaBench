#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {void* modulation; } ;
struct TYPE_17__ {unsigned int symbol_rate; void* modulation; void* fec_inner; } ;
struct TYPE_16__ {unsigned int symbol_rate; void* fec_inner; } ;
struct TYPE_15__ {int transmission_mode; int guard_interval; int hierarchy_information; void* constellation; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_19__ {TYPE_4__ vsb; TYPE_3__ qam; TYPE_2__ qpsk; TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {int num; unsigned int frequency; void* inversion; TYPE_5__ u; struct dtv_property* props; } ;
struct dvb_frontend_event {int num; unsigned int frequency; void* inversion; TYPE_5__ u; struct dtv_property* props; } ;
struct TYPE_21__ {unsigned int data; } ;
struct dtv_property {int /*<<< orphan*/  cmd; TYPE_7__ u; } ;
struct dtv_properties {int num; unsigned int frequency; void* inversion; TYPE_5__ u; struct dtv_property* props; } ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  feparams ;
typedef  int fe_transmit_mode_t ;
typedef  void* fe_spectral_inversion_t ;
typedef  void* fe_modulation_t ;
typedef  int fe_hierarchy_t ;
typedef  int fe_guard_interval_t ;
typedef  void* fe_code_rate_t ;
typedef  int /*<<< orphan*/  fe_bandwidth_t ;
struct TYPE_22__ {size_t cur_adapter; TYPE_6__* adapters; } ;
typedef  TYPE_8__ dvb_state_t ;
struct TYPE_23__ {TYPE_8__* state; } ;
typedef  TYPE_9__ dvb_priv_t ;
struct TYPE_20__ {int /*<<< orphan*/  devno; } ;

/* Variables and functions */
#define  BANDWIDTH_10_MHZ 141 
#define  BANDWIDTH_5_MHZ 140 
#define  BANDWIDTH_6_MHZ 139 
#define  BANDWIDTH_7_MHZ 138 
#define  BANDWIDTH_8_MHZ 137 
#define  BANDWIDTH_AUTO 136 
 int /*<<< orphan*/  DTV_BANDWIDTH_HZ ; 
 int /*<<< orphan*/  DTV_CLEAR ; 
 int /*<<< orphan*/  DTV_CODE_RATE_HP ; 
 int /*<<< orphan*/  DTV_CODE_RATE_LP ; 
 int /*<<< orphan*/  DTV_DELIVERY_SYSTEM ; 
 int /*<<< orphan*/  DTV_FREQUENCY ; 
 int /*<<< orphan*/  DTV_GUARD_INTERVAL ; 
 int /*<<< orphan*/  DTV_HIERARCHY ; 
 int /*<<< orphan*/  DTV_INNER_FEC ; 
 int /*<<< orphan*/  DTV_INVERSION ; 
 int /*<<< orphan*/  DTV_MODULATION ; 
 int /*<<< orphan*/  DTV_PILOT ; 
 int /*<<< orphan*/  DTV_ROLLOFF ; 
 int /*<<< orphan*/  DTV_STREAM_ID ; 
 int /*<<< orphan*/  DTV_SYMBOL_RATE ; 
 int /*<<< orphan*/  DTV_TRANSMISSION_MODE ; 
 int /*<<< orphan*/  DTV_TUNE ; 
 int /*<<< orphan*/  FE_GET_EVENT ; 
 int /*<<< orphan*/  FE_SET_FRONTEND ; 
 int /*<<< orphan*/  FE_SET_PROPERTY ; 
 unsigned int LOF1 ; 
 unsigned int LOF2 ; 
 int /*<<< orphan*/  MP_ERR (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_9__*,char*,...) ; 
 int NO_STREAM_ID_FILTER ; 
 void* PILOT_AUTO ; 
 void* ROLLOFF_AUTO ; 
 unsigned int SLOF ; 
#define  SYS_ATSC 135 
#define  SYS_DVBC_ANNEX_A 134 
#define  SYS_DVBC_ANNEX_B 133 
#define  SYS_DVBC_ANNEX_C 132 
#define  SYS_DVBS 131 
#define  SYS_DVBS2 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 int check_status (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  do_diseqc (int,unsigned int,int,int) ; 
 int /*<<< orphan*/  dvbv5_tune (TYPE_9__*,int,unsigned int,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  get_dvb_delsys (unsigned int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  memset (struct dvb_frontend_parameters*,int,int) ; 

__attribute__((used)) static int tune_it(dvb_priv_t *priv, int fd_frontend, unsigned int delsys,
                   unsigned int freq, unsigned int srate, char pol,
                   int stream_id,
                   fe_spectral_inversion_t specInv, unsigned int diseqc,
                   fe_modulation_t modulation,
                   fe_code_rate_t HP_CodeRate,
                   fe_transmit_mode_t TransmissionMode,
                   fe_guard_interval_t guardInterval,
                   fe_bandwidth_t bandwidth,
                   fe_code_rate_t LP_CodeRate, fe_hierarchy_t hier,
                   int timeout)
{
    int hi_lo = 0, bandwidth_hz = 0;
    dvb_state_t* state = priv->state;
    struct dvb_frontend_parameters feparams;


    MP_VERBOSE(priv, "TUNE_IT, fd_frontend %d, %s freq %lu, srate %lu, "
               "pol %c, diseqc %u\n", fd_frontend,
               get_dvb_delsys(delsys),
               (long unsigned int)freq, (long unsigned int)srate,
               (pol > ' ' ? pol : '-'), diseqc);

    MP_VERBOSE(priv, "Using %s adapter %d\n",
        get_dvb_delsys(delsys),
        state->adapters[state->cur_adapter].devno);

    {
        /* discard stale QPSK events */
        struct dvb_frontend_event ev;
        while (true) {
            if (ioctl(fd_frontend, FE_GET_EVENT, &ev) < 0)
                break;
        }
    }

   /* Prepare params, be verbose. */
    switch (delsys) {
    case SYS_DVBT2:
#ifndef DVB_USE_S2API
        MP_ERR(priv, "ERROR: Can not tune to T2 channel, S2-API not "
                     "available, will tune to DVB-T!\n");
#endif
        /* PASSTROUTH. */
    case SYS_DVBT:
        if (freq < 1000000)
            freq *= 1000UL;
        switch (bandwidth) {
        case BANDWIDTH_5_MHZ:
            bandwidth_hz = 5000000;
            break;
        case BANDWIDTH_6_MHZ:
            bandwidth_hz = 6000000;
            break;
        case BANDWIDTH_7_MHZ:
            bandwidth_hz = 7000000;
            break;
        case BANDWIDTH_8_MHZ:
            bandwidth_hz = 8000000;
            break;
        case BANDWIDTH_10_MHZ:
            bandwidth_hz = 10000000;
            break;
        case BANDWIDTH_AUTO:
            if (freq < 474000000) {
                bandwidth_hz = 7000000;
            } else {
                bandwidth_hz = 8000000;
            }
            break;
        default:
            bandwidth_hz = 0;
            break;
        }

        MP_VERBOSE(priv, "tuning %s to %d Hz, bandwidth: %d\n",
                   get_dvb_delsys(delsys), freq, bandwidth_hz);
        break;
    case SYS_DVBS2:
#ifndef DVB_USE_S2API
        MP_ERR(priv, "ERROR: Can not tune to S2 channel, S2-API not "
                     "available, will tune to DVB-S!\n");
#endif
        /* PASSTROUTH. */
    case SYS_DVBS:
        if (freq > 2200000) {
            // this must be an absolute frequency
            if (freq < SLOF) {
                freq -= LOF1;
                hi_lo = 0;
            } else {
                freq -= LOF2;
                hi_lo = 1;
            }
        }
        MP_VERBOSE(priv, "tuning %s to Freq: %u, Pol: %c Srate: %d, "
                   "22kHz: %s, LNB:  %d\n", get_dvb_delsys(delsys), freq,
                   pol, srate, hi_lo ? "on" : "off", diseqc);

        if (do_diseqc(fd_frontend, diseqc, (pol == 'V' ? 1 : 0), hi_lo) == 0) {
            MP_VERBOSE(priv, "DISEQC setting succeeded\n");
        } else {
            MP_ERR(priv, "DISEQC setting failed\n");
            return -1;
        }

        break;
    case SYS_DVBC_ANNEX_A:
    case SYS_DVBC_ANNEX_C:
        MP_VERBOSE(priv, "tuning %s to %d, srate=%d\n",
                   get_dvb_delsys(delsys), freq, srate);
        break;
#ifdef DVB_ATSC
    case SYS_ATSC:
    case SYS_DVBC_ANNEX_B:
        MP_VERBOSE(priv, "tuning %s to %d, modulation=%d\n",
                   get_dvb_delsys(delsys), freq, modulation);
        break;
#endif
    default:
        MP_VERBOSE(priv, "Unknown FE type. Aborting\n");
        return 0;
    }

#ifdef DVB_USE_S2API
    /* S2API is the DVB API new since 2.6.28.
     * It is needed to tune to new delivery systems, e.g. DVB-S2.
     * It takes a struct with a list of pairs of command + parameter.
     */

    /* Reset before tune. */
    struct dtv_property p_clear[] = {
        { .cmd = DTV_CLEAR },
    };
    struct dtv_properties cmdseq_clear = {
        .num = 1,
        .props = p_clear
    };
    if (ioctl(fd_frontend, FE_SET_PROPERTY, &cmdseq_clear) < 0) {
        MP_ERR(priv, "FE_SET_PROPERTY DTV_CLEAR failed\n");
    }

    /* Tune. */
    switch (delsys) {
    case SYS_DVBS:
    case SYS_DVBS2:
        {
            struct dtv_property p[] = {
                { .cmd = DTV_DELIVERY_SYSTEM, .u.data = delsys },
                { .cmd = DTV_FREQUENCY, .u.data = freq },
                { .cmd = DTV_MODULATION, .u.data = modulation },
                { .cmd = DTV_SYMBOL_RATE, .u.data = srate },
                { .cmd = DTV_INNER_FEC, .u.data = HP_CodeRate },
                { .cmd = DTV_INVERSION, .u.data = specInv },
                { .cmd = DTV_ROLLOFF, .u.data = ROLLOFF_AUTO },
                { .cmd = DTV_PILOT, .u.data = PILOT_AUTO },
                { .cmd = DTV_TUNE },
            };
            struct dtv_properties cmdseq = {
                .num = sizeof(p) / sizeof(p[0]),
                .props = p
            };
            if (dvbv5_tune(priv, fd_frontend, delsys, &cmdseq) != 0) {
                goto old_api;
            }
        }
        break;
    case SYS_DVBT:
    case SYS_DVBT2:
        {
            struct dtv_property p[] = {
                { .cmd = DTV_DELIVERY_SYSTEM, .u.data = delsys },
                { .cmd = DTV_FREQUENCY, .u.data = freq },
                { .cmd = DTV_MODULATION, .u.data = modulation },
                { .cmd = DTV_SYMBOL_RATE, .u.data = srate },
                { .cmd = DTV_CODE_RATE_HP, .u.data = HP_CodeRate },
                { .cmd = DTV_CODE_RATE_LP, .u.data = LP_CodeRate },
                { .cmd = DTV_INVERSION, .u.data = specInv },
                { .cmd = DTV_BANDWIDTH_HZ, .u.data = bandwidth_hz },
                { .cmd = DTV_TRANSMISSION_MODE, .u.data = TransmissionMode },
                { .cmd = DTV_GUARD_INTERVAL, .u.data = guardInterval },
                { .cmd = DTV_HIERARCHY, .u.data = hier },
                { .cmd = DTV_STREAM_ID, .u.data = stream_id },
                { .cmd = DTV_TUNE },
            };
            struct dtv_properties cmdseq = {
                .num = sizeof(p) / sizeof(p[0]),
                .props = p
            };
            if (dvbv5_tune(priv, fd_frontend, delsys, &cmdseq) != 0) {
                goto old_api;
            }
        }
        break;
    case SYS_DVBC_ANNEX_A:
    case SYS_DVBC_ANNEX_C:
        {
            struct dtv_property p[] = {
                { .cmd = DTV_DELIVERY_SYSTEM, .u.data = delsys },
                { .cmd = DTV_FREQUENCY, .u.data = freq },
                { .cmd = DTV_MODULATION, .u.data = modulation },
                { .cmd = DTV_SYMBOL_RATE, .u.data = srate },
                { .cmd = DTV_INNER_FEC, .u.data = HP_CodeRate },
                { .cmd = DTV_INVERSION, .u.data = specInv },
                { .cmd = DTV_TUNE },
            };
            struct dtv_properties cmdseq = {
                .num = sizeof(p) / sizeof(p[0]),
                .props = p
            };
            if (dvbv5_tune(priv, fd_frontend, delsys, &cmdseq) != 0) {
                goto old_api;
            }
        }
        break;
#ifdef DVB_ATSC
    case SYS_ATSC:
    case SYS_DVBC_ANNEX_B:
        {
            struct dtv_property p[] = {
                { .cmd = DTV_DELIVERY_SYSTEM, .u.data = delsys },
                { .cmd = DTV_FREQUENCY, .u.data = freq },
                { .cmd = DTV_INVERSION, .u.data = specInv },
                { .cmd = DTV_MODULATION, .u.data = modulation },
                { .cmd = DTV_TUNE },
            };
            struct dtv_properties cmdseq = {
                .num = sizeof(p) / sizeof(p[0]),
                .props = p
            };
            if (dvbv5_tune(priv, fd_frontend, delsys, &cmdseq) != 0) {
                goto old_api;
            }
        }
        break;
#endif
    }

    int tune_status = check_status(priv, fd_frontend, timeout);
    if (tune_status != 0) {
        MP_ERR(priv, "ERROR locking to channel when tuning with S2API, clearing and falling back to DVBv3-tuning.\n");
        if (ioctl(fd_frontend, FE_SET_PROPERTY, &cmdseq_clear) < 0) {
            MP_ERR(priv, "FE_SET_PROPERTY DTV_CLEAR failed\n");
        }
        goto old_api;
    } else {
        return tune_status;
    }

old_api:
#endif

    MP_VERBOSE(priv, "Tuning via DVB-API version 3.\n");

    if (stream_id != NO_STREAM_ID_FILTER && stream_id != 0) {
        MP_ERR(priv, "DVB-API version 3 does not support stream_id (PLP).\n");
        return -1;
    }
    memset(&feparams, 0x00, sizeof(feparams));
    feparams.frequency = freq;
    feparams.inversion = specInv;

    switch (delsys) {
    case SYS_DVBT:
    case SYS_DVBT2:
        feparams.u.ofdm.bandwidth = bandwidth;
        feparams.u.ofdm.code_rate_HP = HP_CodeRate;
        feparams.u.ofdm.code_rate_LP = LP_CodeRate;
        feparams.u.ofdm.constellation = modulation;
        feparams.u.ofdm.transmission_mode = TransmissionMode;
        feparams.u.ofdm.guard_interval = guardInterval;
        feparams.u.ofdm.hierarchy_information = hier;
        break;
    case SYS_DVBS:
    case SYS_DVBS2:
        feparams.u.qpsk.symbol_rate = srate;
        feparams.u.qpsk.fec_inner = HP_CodeRate;
        break;
    case SYS_DVBC_ANNEX_A:
    case SYS_DVBC_ANNEX_C:
        feparams.u.qam.symbol_rate = srate;
        feparams.u.qam.fec_inner = HP_CodeRate;
        feparams.u.qam.modulation = modulation;
        break;
#ifdef DVB_ATSC
    case SYS_ATSC:
    case SYS_DVBC_ANNEX_B:
        feparams.u.vsb.modulation = modulation;
        break;
#endif
    }

    if (ioctl(fd_frontend, FE_SET_FRONTEND, &feparams) < 0) {
        MP_ERR(priv, "ERROR tuning channel\n");
        return -1;
    }

    return check_status(priv, fd_frontend, timeout);
}