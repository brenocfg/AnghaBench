#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct mpv_global {int dummy; } ;
struct mp_log {int dummy; } ;
struct TYPE_18__ {TYPE_4__* priv; struct mpv_global* global; struct mp_log* log; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_19__ {int switching_channel; int stream_used; int fe_fd; int dvr_fd; int adapters_count; TYPE_6__* adapters; scalar_t__ is_on; } ;
typedef  TYPE_3__ dvb_state_t ;
struct TYPE_20__ {TYPE_1__* opts; } ;
typedef  TYPE_4__ dvb_priv_t ;
typedef  TYPE_3__ dvb_channels_list_t ;
struct TYPE_21__ {unsigned int devno; TYPE_3__* list; int /*<<< orphan*/  delsys_mask; } ;
typedef  TYPE_6__ dvb_adapter_config_t ;
struct TYPE_17__ {char* cfg_file; int /*<<< orphan*/  cfg_full_transponder; } ;

/* Variables and functions */
 scalar_t__ DELSYS_IS_SET (unsigned int,int) ; 
 unsigned int DELSYS_SUPP_MASK ; 
 unsigned int MAX_ADAPTERS ; 
 int MAX_FRONTENDS ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int PATH_MAX ; 
#define  SYS_ATSC 134 
#define  SYS_DVBC_ANNEX_A 133 
#define  SYS_DVBC_ANNEX_C 132 
#define  SYS_DVBS 131 
#define  SYS_DVBS2 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 unsigned int SYS_DVB__COUNT__ ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_3__* dvb_get_channels (struct mp_log*,TYPE_3__*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 unsigned int dvb_get_tuner_delsys_mask (int,struct mp_log*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* global_dvb_state ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned int**,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,unsigned int) ; 
 char* mp_find_config_file (void*,struct mpv_global*,char const*) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,...) ; 
 int open (char*,int) ; 
 TYPE_6__* realloc (TYPE_6__*,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

dvb_state_t *dvb_get_state(stream_t *stream)
{
    if (global_dvb_state != NULL) {
      return global_dvb_state;
    }
    struct mp_log *log = stream->log;
    struct mpv_global *global = stream->global;
    dvb_priv_t *priv = stream->priv;
    unsigned int delsys, delsys_mask[MAX_FRONTENDS], size;
    char filename[PATH_MAX], *conf_file;
    const char *conf_file_name;
    void *talloc_ctx;
    dvb_channels_list_t *list;
    dvb_adapter_config_t *adapters = NULL, *tmp;
    dvb_state_t *state = NULL;

    state = malloc(sizeof(dvb_state_t));
    if (state == NULL)
        return NULL;
    memset(state, 0x00, sizeof(dvb_state_t));
    state->switching_channel = false;
    state->is_on = 0;
    state->stream_used = true;
    state->fe_fd = state->dvr_fd = -1;
    for (unsigned int i = 0; i < MAX_ADAPTERS; i++) {
        list = NULL;
        for (unsigned int f = 0; f < MAX_FRONTENDS; f++) {
            snprintf(filename, sizeof(filename), "/dev/dvb/adapter%u/frontend%u", i, f);
            int fd = open(filename, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
            if (fd < 0)
                continue;

            mp_verbose(log, "Opened device %s, FD: %d\n", filename, fd);
            delsys_mask[f] = dvb_get_tuner_delsys_mask(fd, log);
            delsys_mask[f] &= DELSYS_SUPP_MASK; /* Filter unsupported delivery systems. */
            close(fd);
            if (delsys_mask[f] == 0) {
                mp_verbose(log, "Frontend device %s has no supported delivery systems.\n",
                       filename);
                continue; /* Skip tuner. */
            }
            mp_verbose(log, "Frontend device %s offers some supported delivery systems.\n",
                   filename);
            /* Create channel list for adapter. */
            for (delsys = 0; delsys < SYS_DVB__COUNT__; delsys++) {
                if (!DELSYS_IS_SET(delsys_mask[f], delsys))
                    continue; /* Skip unsupported. */

                switch (delsys) {
                case SYS_DVBC_ANNEX_A:
                case SYS_DVBC_ANNEX_C:
                    conf_file_name = "channels.conf.cbl";
                    break;
                case SYS_ATSC:
                    conf_file_name = "channels.conf.atsc";
                    break;
                case SYS_DVBT:
                    if (DELSYS_IS_SET(delsys_mask[f], SYS_DVBT2))
                        continue; /* Add all channels later with T2. */
                    /* PASSTOUTH */
                case SYS_DVBT2:
                    conf_file_name = "channels.conf.ter";
                    break;
                case SYS_DVBS:
                    if (DELSYS_IS_SET(delsys_mask[f], SYS_DVBS2))
                        continue; /* Add all channels later with S2. */
                    /* PASSTOUTH */
                case SYS_DVBS2:
                    conf_file_name = "channels.conf.sat";
                    break;
                default:
                    continue;
                }

                if (priv->opts->cfg_file && priv->opts->cfg_file[0]) {
                    talloc_ctx = NULL;
                    conf_file = priv->opts->cfg_file;
                } else {
                    talloc_ctx = talloc_new(NULL);
                    conf_file = mp_find_config_file(talloc_ctx, global, conf_file_name);
                    if (conf_file) {
                        mp_verbose(log, "Ignoring other channels.conf files.\n");
                    } else {
                        conf_file = mp_find_config_file(talloc_ctx, global,
                                        "channels.conf");
                    }
                }

                list = dvb_get_channels(log, list, priv->opts->cfg_full_transponder,
                                        conf_file, f, delsys, delsys_mask[f]);
                talloc_free(talloc_ctx);
            }
        }
        /* Add adapter with non zero channel list. */
        if (list == NULL)
            continue;

        size = sizeof(dvb_adapter_config_t) * (state->adapters_count + 1);
        tmp = realloc(state->adapters, size);

        if (tmp == NULL) {
            mp_err(log, "DVB_CONFIG, can't realloc %d bytes, skipping\n",
                   size);
            free(list);
            continue;
        }
        adapters = tmp;

        state->adapters = adapters;
        state->adapters[state->adapters_count].devno = i;
        memcpy(&state->adapters[state->adapters_count].delsys_mask,
            &delsys_mask, (sizeof(unsigned int) * MAX_FRONTENDS));
        state->adapters[state->adapters_count].list = list;
        state->adapters_count++;
    }

    if (state->adapters_count == 0) {
        free(state);
        state = NULL;
    }

    global_dvb_state = state;
    return state;
}