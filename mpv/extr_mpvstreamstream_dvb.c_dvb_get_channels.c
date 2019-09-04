#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct TYPE_13__ {char* name; size_t pids_cnt; unsigned long freq; int service_id; int is_dvb_x2; unsigned int frontend; int delsys; unsigned int diseqc; unsigned long srate; int NUM_CHANNELS; int* pids; struct TYPE_13__* channels; int /*<<< orphan*/  hier; void* cr_lp; int /*<<< orphan*/  gi; void* trans; int /*<<< orphan*/  bw; int /*<<< orphan*/  mod; void* cr; int /*<<< orphan*/  inv; int /*<<< orphan*/  pol; int /*<<< orphan*/  stream_id; } ;
typedef  TYPE_1__ dvb_channels_list_t ;
typedef  TYPE_1__ dvb_channel_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_10_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_5_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_6_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_7_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_8_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_AUTO ; 
 int CHANNEL_LINE_LEN ; 
 int /*<<< orphan*/  DELSYS_IS_SET (unsigned int,int) ; 
 void* FEC_1_2 ; 
 void* FEC_2_3 ; 
 void* FEC_3_4 ; 
 void* FEC_4_5 ; 
 void* FEC_5_6 ; 
 void* FEC_6_7 ; 
 void* FEC_7_8 ; 
 void* FEC_8_9 ; 
 void* FEC_AUTO ; 
 void* FEC_NONE ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_AUTO ; 
 int /*<<< orphan*/  HIERARCHY_1 ; 
 int /*<<< orphan*/  HIERARCHY_2 ; 
 int /*<<< orphan*/  HIERARCHY_4 ; 
 int /*<<< orphan*/  HIERARCHY_AUTO ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  INVERSION_AUTO ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  NO_STREAM_ID_FILTER ; 
 int /*<<< orphan*/  QAM_128 ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_256 ; 
 int /*<<< orphan*/  QAM_32 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QAM_AUTO ; 
#define  SYS_ATSC 135 
#define  SYS_DVBC_ANNEX_A 134 
#define  SYS_DVBC_ANNEX_B 133 
#define  SYS_DVBC_ANNEX_C 132 
#define  SYS_DVBS 131 
#define  SYS_DVBS2 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 void* TRANSMISSION_MODE_2K ; 
 void* TRANSMISSION_MODE_8K ; 
 void* TRANSMISSION_MODE_AUTO ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  get_dvb_delsys (int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*,char*) ; 
 int /*<<< orphan*/  mp_toupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,...) ; 
 scalar_t__ parse_pid_string (struct mp_log*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  parse_vdr_par_string (char*,TYPE_1__*) ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int sscanf (char*,char const*,...) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static dvb_channels_list_t *dvb_get_channels(struct mp_log *log,
                                           dvb_channels_list_t *list_add,
                                           int cfg_full_transponder,
                                           char *filename,
                                           unsigned int frontend,
                                           int delsys, unsigned int delsys_mask)
{
    dvb_channels_list_t *list = list_add;
    FILE *f;
    char line[CHANNEL_LINE_LEN], *colon;

    if (!filename)
        return NULL;

    int fields, cnt, k;
    int has8192, has0;
    dvb_channel_t *ptr, *tmp, chn;
    char tmp_lcr[256], tmp_hier[256], inv[256], bw[256], cr[256], mod[256],
         transm[256], gi[256], vpid_str[256], apid_str[256], tpid_str[256],
         vdr_par_str[256], vdr_loc_str[256];
    const char *cbl_conf =
        "%d:%255[^:]:%d:%255[^:]:%255[^:]:%255[^:]:%255[^:]\n";
    const char *sat_conf = "%d:%c:%d:%d:%255[^:]:%255[^:]\n";
    const char *ter_conf =
        "%d:%255[^:]:%255[^:]:%255[^:]:%255[^:]:%255[^:]:%255[^:]:%255[^:]:%255[^:]:%255[^:]:%255[^:]\n";
#ifdef DVB_ATSC
    const char *atsc_conf = "%d:%255[^:]:%255[^:]:%255[^:]\n";
#endif
    const char *vdr_conf =
        "%d:%255[^:]:%255[^:]:%d:%255[^:]:%255[^:]:%255[^:]:%*255[^:]:%d:%*d:%*d:%*d\n%n";

    mp_verbose(log, "CONFIG_READ FILE: %s, type: %s\n",
               filename, get_dvb_delsys(delsys));
    if ((f = fopen(filename, "r")) == NULL) {
        mp_fatal(log, "CAN'T READ CONFIG FILE %s\n", filename);
        return NULL;
    }

    if (list == NULL) {
        list = malloc(sizeof(dvb_channels_list_t));
        if (list == NULL) {
            fclose(f);
            mp_verbose(log, "DVB_GET_CHANNELS: couldn't malloc enough memory\n");
            return NULL;
        }
        memset(list, 0x00, sizeof(dvb_channels_list_t));
    }

    ptr = &chn;
    while (!feof(f)) {
        if (fgets(line, CHANNEL_LINE_LEN, f) == NULL)
            continue;

        if ((line[0] == '#') || (strlen(line) == 0))
            continue;

        memset(ptr, 0x00, sizeof(dvb_channel_t));
        vpid_str[0] = apid_str[0] = tpid_str[0] = 0;
        vdr_loc_str[0] = vdr_par_str[0] = 0;

        colon = strchr(line, ':');
        if (colon) {
            k = colon - line;
            if (!k)
                continue;
            // In some modern VDR-style configs, channel name also has bouquet after ;.
            // Parse that off, we ignore it.
            char *bouquet_sep = strchr(line, ';');
            int channel_name_length = k;
            if (bouquet_sep && bouquet_sep < colon)
                channel_name_length = (bouquet_sep - line);
            ptr->name = malloc((channel_name_length + 1));
            if (!ptr->name)
                continue;
            av_strlcpy(ptr->name, line, (channel_name_length + 1));
        } else {
            continue;
        }
        k++;
        ptr->pids_cnt = 0;
        ptr->freq = 0;
        ptr->service_id = -1;
        ptr->is_dvb_x2 = false;
        ptr->frontend = frontend;
        ptr->delsys = delsys;
        ptr->diseqc = 0;
        ptr->stream_id = NO_STREAM_ID_FILTER;
        ptr->inv = INVERSION_AUTO;
        ptr->bw = BANDWIDTH_AUTO;
        ptr->cr = FEC_AUTO;
        ptr->cr_lp = FEC_AUTO;
        ptr->mod = QAM_AUTO;
        ptr->hier = HIERARCHY_AUTO;
        ptr->gi = GUARD_INTERVAL_AUTO;
        ptr->trans = TRANSMISSION_MODE_AUTO;

        // Check if VDR-type channels.conf-line - then full line is consumed by the scan.
        int num_chars = 0;
        fields = sscanf(&line[k], vdr_conf,
                        &ptr->freq, vdr_par_str, vdr_loc_str, &ptr->srate,
                        vpid_str, apid_str, tpid_str, &ptr->service_id,
                        &num_chars);

        if (num_chars == strlen(&line[k])) {
            // Modulation parsed here, not via old xine-parsing path.
            mod[0] = '\0';
            // It's a VDR-style config line.
            parse_vdr_par_string(vdr_par_str, ptr);
            // Units in VDR-style config files are divided by 1000.
            ptr->freq *=  1000UL;
            ptr->srate *=  1000UL;
            switch (delsys) {
            case SYS_DVBT:
            case SYS_DVBT2:
                /* Fix delsys value. */
                if (ptr->is_dvb_x2) {
                    ptr->delsys = delsys = SYS_DVBT2;
                } else {
                    ptr->delsys = delsys = SYS_DVBT;
                }
                if (!DELSYS_IS_SET(delsys_mask, delsys))
                    continue; /* Skip channel. */
               /* PASSTROUTH */
            case SYS_DVBC_ANNEX_A:
            case SYS_DVBC_ANNEX_C:
            case SYS_ATSC:
            case SYS_DVBC_ANNEX_B:
                mp_verbose(log, "VDR, %s, NUM: %d, NUM_FIELDS: %d, NAME: %s, "
                           "FREQ: %d, SRATE: %d",
                           get_dvb_delsys(delsys),
                           list->NUM_CHANNELS, fields,
                           ptr->name, ptr->freq, ptr->srate);
                break;
            case SYS_DVBS:
            case SYS_DVBS2:
                /* Fix delsys value. */
                if (ptr->is_dvb_x2) {
                    ptr->delsys = delsys = SYS_DVBS2;
                } else {
                    ptr->delsys = delsys = SYS_DVBS;
                }
                if (!DELSYS_IS_SET(delsys_mask, delsys))
                    continue; /* Skip channel. */

                if (vdr_loc_str[0]) {
                    // In older vdr config format, this field contained the DISEQc information.
                    // If it is numeric, assume that's it.
                    int diseqc_info = 0;
                    int valid_digits = 0;
                    if (sscanf(vdr_loc_str, "%d%n", &diseqc_info,
                               &valid_digits) == 1)
                    {
                        if (valid_digits == strlen(vdr_loc_str)) {
                            ptr->diseqc = (unsigned int)diseqc_info;
                            if (ptr->diseqc > 4)
                                continue;
                            if (ptr->diseqc > 0)
                                ptr->diseqc--;
                        }
                    }
                }

                mp_verbose(log, "%s NUM: %d, NUM_FIELDS: %d, NAME: %s, "
                           "FREQ: %d, SRATE: %d, POL: %c, DISEQC: %d, S2: %s, "
                           "StreamID: %d, SID: %d",
                           get_dvb_delsys(delsys),
                           list->NUM_CHANNELS,
                           fields, ptr->name, ptr->freq, ptr->srate, ptr->pol,
                           ptr->diseqc, (delsys == SYS_DVBS2) ? "yes" : "no",
                           ptr->stream_id, ptr->service_id);
                break;
            default:
                break;
            }
        } else {
            switch (delsys) {
            case SYS_DVBT:
            case SYS_DVBT2:
                fields = sscanf(&line[k], ter_conf,
                                &ptr->freq, inv, bw, cr, tmp_lcr, mod,
                                transm, gi, tmp_hier, vpid_str, apid_str);
                mp_verbose(log, "%s, NUM: %d, NUM_FIELDS: %d, NAME: %s, FREQ: %d",
                           get_dvb_delsys(delsys), list->NUM_CHANNELS,
                           fields, ptr->name, ptr->freq);
                break;
            case SYS_DVBC_ANNEX_A:
            case SYS_DVBC_ANNEX_C:
                fields = sscanf(&line[k], cbl_conf,
                                &ptr->freq, inv, &ptr->srate,
                                cr, mod, vpid_str, apid_str);
                mp_verbose(log, "%s, NUM: %d, NUM_FIELDS: %d, NAME: %s, FREQ: %d, "
                           "SRATE: %d",
                           get_dvb_delsys(delsys),
                           list->NUM_CHANNELS, fields, ptr->name,
                           ptr->freq, ptr->srate);
                break;
#ifdef DVB_ATSC
            case SYS_ATSC:
            case SYS_DVBC_ANNEX_B:
                fields = sscanf(&line[k], atsc_conf,
                                &ptr->freq, mod, vpid_str, apid_str);
                mp_verbose(log, "%s, NUM: %d, NUM_FIELDS: %d, NAME: %s, FREQ: %d\n",
                           get_dvb_delsys(delsys), list->NUM_CHANNELS,
                           fields, ptr->name, ptr->freq);
                break;
#endif
            case SYS_DVBS:
            case SYS_DVBS2:
                fields = sscanf(&line[k], sat_conf,
                                &ptr->freq, &ptr->pol, &ptr->diseqc, &ptr->srate,
                                vpid_str,
                                apid_str);
                ptr->pol = mp_toupper(ptr->pol);
                ptr->freq *=  1000UL;
                ptr->srate *=  1000UL;
                if (ptr->diseqc > 4)
                    continue;
                if (ptr->diseqc > 0)
                    ptr->diseqc--;
                mp_verbose(log, "%s, NUM: %d, NUM_FIELDS: %d, NAME: %s, FREQ: %d, "
                           "SRATE: %d, POL: %c, DISEQC: %d",
                           get_dvb_delsys(delsys),
                           list->NUM_CHANNELS, fields, ptr->name, ptr->freq,
                           ptr->srate, ptr->pol, ptr->diseqc);
                break;
            default:
                break;
            }
        }

        if (parse_pid_string(log, vpid_str, ptr))
            fields++;
        if (parse_pid_string(log, apid_str, ptr))
            fields++;
                 /* If we do not know the service_id, PMT can not be extracted.
                    Teletext decoding will fail without PMT. */
        if (ptr->service_id != -1) {
            if (parse_pid_string(log, tpid_str, ptr))
                fields++;
        }


        if (fields < 2 || ptr->pids_cnt == 0 || ptr->freq == 0 ||
            strlen(ptr->name) == 0)
            continue;

        /* Add some PIDs which are mandatory in DVB,
         * and contain human-readable helpful data. */

        /* This is the STD, the service description table.
         * It contains service names and such, ffmpeg decodes it. */
        ptr->pids[ptr->pids_cnt] = 0x0011;
        ptr->pids_cnt++;

        /* This is the EIT, which contains EPG data.
         * ffmpeg can not decode it (yet), but e.g. VLC
         * shows what was recorded. */
        ptr->pids[ptr->pids_cnt] = 0x0012;
        ptr->pids_cnt++;

        if (ptr->service_id != -1) {
            /* We have the PMT-PID in addition.
               This will be found later, when we tune to the channel.
               Push back here to create the additional demux. */
            ptr->pids[ptr->pids_cnt] = -1;       // Placeholder.
            ptr->pids_cnt++;
        }

        has8192 = has0 = 0;
        for (cnt = 0; cnt < ptr->pids_cnt; cnt++) {
            if (ptr->pids[cnt] == 8192)
                has8192 = 1;
            if (ptr->pids[cnt] == 0)
                has0 = 1;
        }

        /* 8192 is the pseudo-PID for full TP dump,
           enforce that if requested. */
        if (!has8192 && cfg_full_transponder)
            has8192 = 1;
        if (has8192) {
            ptr->pids[0] = 8192;
            ptr->pids_cnt = 1;
        } else if (!has0) {
            ptr->pids[ptr->pids_cnt] = 0;               //PID 0 is the PAT
            ptr->pids_cnt++;
        }

        mp_verbose(log, " PIDS: ");
        for (cnt = 0; cnt < ptr->pids_cnt; cnt++)
            mp_verbose(log, " %d ", ptr->pids[cnt]);
        mp_verbose(log, "\n");

        switch (delsys) {
        case SYS_DVBT:
        case SYS_DVBT2:
        case SYS_DVBC_ANNEX_A:
        case SYS_DVBC_ANNEX_C:
            if (!strcmp(inv, "INVERSION_ON")) {
                ptr->inv = INVERSION_ON;
            } else if (!strcmp(inv, "INVERSION_OFF")) {
                ptr->inv = INVERSION_OFF;
            }


            if (!strcmp(cr, "FEC_1_2")) {
                ptr->cr = FEC_1_2;
            } else if (!strcmp(cr, "FEC_2_3")) {
                ptr->cr = FEC_2_3;
            } else if (!strcmp(cr, "FEC_3_4")) {
                ptr->cr = FEC_3_4;
            } else if (!strcmp(cr, "FEC_4_5")) {
                ptr->cr = FEC_4_5;
            } else if (!strcmp(cr, "FEC_6_7")) {
                ptr->cr = FEC_6_7;
            } else if (!strcmp(cr, "FEC_8_9")) {
                ptr->cr = FEC_8_9;
            } else if (!strcmp(cr, "FEC_5_6")) {
                ptr->cr = FEC_5_6;
            } else if (!strcmp(cr, "FEC_7_8")) {
                ptr->cr = FEC_7_8;
            } else if (!strcmp(cr, "FEC_NONE")) {
                ptr->cr = FEC_NONE;
            }
        }

        switch (delsys) {
        case SYS_DVBT:
        case SYS_DVBT2:
        case SYS_DVBC_ANNEX_A:
        case SYS_DVBC_ANNEX_C:
        case SYS_ATSC:
        case SYS_DVBC_ANNEX_B:
            if (!strcmp(mod, "QAM_128")) {
                ptr->mod = QAM_128;
            } else if (!strcmp(mod, "QAM_256")) {
                ptr->mod = QAM_256;
            } else if (!strcmp(mod, "QAM_64")) {
                ptr->mod = QAM_64;
            } else if (!strcmp(mod, "QAM_32")) {
                ptr->mod = QAM_32;
            } else if (!strcmp(mod, "QAM_16")) {
                ptr->mod = QAM_16;
#ifdef DVB_ATSC
            } else if (!strcmp(mod, "VSB_8") || !strcmp(mod, "8VSB")) {
                ptr->mod = VSB_8;
            } else if (!strcmp(mod, "VSB_16") || !strcmp(mod, "16VSB")) {
                ptr->mod = VSB_16;
#endif
            }
        }
#ifdef DVB_ATSC
        /* Modulation defines real delsys for ATSC:
           Terrestrial (VSB) is SYS_ATSC, Cable (QAM) is SYS_DVBC_ANNEX_B. */
        if (delsys == SYS_ATSC || delsys == SYS_DVBC_ANNEX_B) {
            if (ptr->mod == VSB_8 || ptr->mod == VSB_16) {
                delsys = SYS_ATSC;
            } else {
                delsys = SYS_DVBC_ANNEX_B;
            }
            if (!DELSYS_IS_SET(delsys_mask, delsys))
                continue; /* Skip channel. */
            mp_verbose(log, "Switched to delivery system for ATSC: %s (guessed from modulation).\n",
                       get_dvb_delsys(delsys));
        }
#endif

        switch (delsys) {
        case SYS_DVBT:
        case SYS_DVBT2:
            if (!strcmp(bw, "BANDWIDTH_5_MHZ")) {
                ptr->bw = BANDWIDTH_5_MHZ;
            } else if (!strcmp(bw, "BANDWIDTH_6_MHZ")) {
                ptr->bw = BANDWIDTH_6_MHZ;
            } else if (!strcmp(bw, "BANDWIDTH_7_MHZ")) {
                ptr->bw = BANDWIDTH_7_MHZ;
            } else if (!strcmp(bw, "BANDWIDTH_8_MHZ")) {
                ptr->bw = BANDWIDTH_8_MHZ;
            } else if (!strcmp(bw, "BANDWIDTH_10_MHZ")) {
                ptr->bw = BANDWIDTH_10_MHZ;
            }


            if (!strcmp(transm, "TRANSMISSION_MODE_2K")) {
                ptr->trans = TRANSMISSION_MODE_2K;
            } else if (!strcmp(transm, "TRANSMISSION_MODE_8K")) {
                ptr->trans = TRANSMISSION_MODE_8K;
            } else if (!strcmp(transm, "TRANSMISSION_MODE_AUTO")) {
                ptr->trans = TRANSMISSION_MODE_AUTO;
            }

            if (!strcmp(gi, "GUARD_INTERVAL_1_32")) {
                ptr->gi = GUARD_INTERVAL_1_32;
            } else if (!strcmp(gi, "GUARD_INTERVAL_1_16")) {
                ptr->gi = GUARD_INTERVAL_1_16;
            } else if (!strcmp(gi, "GUARD_INTERVAL_1_8")) {
                ptr->gi = GUARD_INTERVAL_1_8;
            } else if (!strcmp(gi, "GUARD_INTERVAL_1_4")) {
                ptr->gi = GUARD_INTERVAL_1_4;
            }

            if (!strcmp(tmp_lcr, "FEC_1_2")) {
                ptr->cr_lp = FEC_1_2;
            } else if (!strcmp(tmp_lcr, "FEC_2_3")) {
                ptr->cr_lp = FEC_2_3;
            } else if (!strcmp(tmp_lcr, "FEC_3_4")) {
                ptr->cr_lp = FEC_3_4;
            } else if (!strcmp(tmp_lcr, "FEC_4_5")) {
                ptr->cr_lp = FEC_4_5;
            } else if (!strcmp(tmp_lcr, "FEC_6_7")) {
                ptr->cr_lp = FEC_6_7;
            } else if (!strcmp(tmp_lcr, "FEC_8_9")) {
                ptr->cr_lp = FEC_8_9;
            } else if (!strcmp(tmp_lcr, "FEC_5_6")) {
                ptr->cr_lp = FEC_5_6;
            } else if (!strcmp(tmp_lcr, "FEC_7_8")) {
                ptr->cr_lp = FEC_7_8;
            } else if (!strcmp(tmp_lcr, "FEC_NONE")) {
                ptr->cr_lp = FEC_NONE;
            }


            if (!strcmp(tmp_hier, "HIERARCHY_1")) {
                ptr->hier = HIERARCHY_1;
            } else if (!strcmp(tmp_hier, "HIERARCHY_2")) {
                ptr->hier = HIERARCHY_2;
            } else if (!strcmp(tmp_hier, "HIERARCHY_4")) {
                ptr->hier = HIERARCHY_4;
            } else if (!strcmp(tmp_hier, "HIERARCHY_NONE")) {
                ptr->hier = HIERARCHY_NONE;
            }
        }

        tmp = realloc(list->channels, sizeof(dvb_channel_t) *
                      (list->NUM_CHANNELS + 1));
        if (tmp == NULL)
            break;

        list->channels = tmp;
        memcpy(&(list->channels[list->NUM_CHANNELS]), ptr, sizeof(dvb_channel_t));
        list->NUM_CHANNELS++;
        if (sizeof(dvb_channel_t) * list->NUM_CHANNELS >= 1024 * 1024) {
            mp_verbose(log, "dvbin.c, > 1MB allocated for channels struct, "
                            "dropping the rest of the file\n");
            break;
        }
    }

    fclose(f);
    if (list->NUM_CHANNELS == 0) {
        free(list->channels);
        free(list);
        return NULL;
    }

    return list;
}