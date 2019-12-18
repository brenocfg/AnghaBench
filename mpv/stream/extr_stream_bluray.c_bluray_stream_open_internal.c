#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct bluray_priv_s {char* cfg_device; int num_titles; int current_angle; int current_title; scalar_t__ use_nav; int /*<<< orphan*/ * bd; } ;
struct TYPE_12__ {char* demuxer; struct bluray_priv_s* priv; int /*<<< orphan*/  control; int /*<<< orphan*/  close; int /*<<< orphan*/  fill_buffer; int /*<<< orphan*/  log; int /*<<< orphan*/  global; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_13__ {int duration; int /*<<< orphan*/  playlist; } ;
typedef  TYPE_2__ BLURAY_TITLE_INFO ;
typedef  int /*<<< orphan*/  BLURAY ;

/* Variables and functions */
 int BLURAY_DEFAULT_TITLE ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  MP_FATAL (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  MP_INFO (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  MSGL_DEBUG ; 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  TITLES_RELEVANT ; 
 int /*<<< orphan*/  bd_free_title_info (TYPE_2__*) ; 
 int /*<<< orphan*/  bd_get_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* bd_get_title_info (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int bd_get_titles (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bd_open (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_set_debug_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bluray_stream_close ; 
 int /*<<< orphan*/  bluray_stream_control ; 
 int /*<<< orphan*/  bluray_stream_fill_buffer ; 
 int /*<<< orphan*/  check_disc_info (TYPE_1__*) ; 
 int /*<<< orphan*/  destruct (struct bluray_priv_s*) ; 
 int /*<<< orphan*/  m_option_type_string ; 
 char* mp_format_time (int,int) ; 
 int /*<<< orphan*/  mp_msg_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_read_option_raw (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  select_initial_title (TYPE_1__*,int) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int bluray_stream_open_internal(stream_t *s)
{
    struct bluray_priv_s *b = s->priv;

    char *device = NULL;
    /* find the requested device */
    if (b->cfg_device && b->cfg_device[0]) {
        device = b->cfg_device;
    } else {
        mp_read_option_raw(s->global, "bluray-device", &m_option_type_string,
                           &device);
    }

    if (!device || !device[0]) {
        MP_ERR(s, "No Blu-ray device/location was specified ...\n");
        return STREAM_UNSUPPORTED;
    }

    if (!mp_msg_test(s->log, MSGL_DEBUG))
        bd_set_debug_mask(0);

    /* open device */
    BLURAY *bd = bd_open(device, NULL);
    if (!bd) {
        MP_ERR(s, "Couldn't open Blu-ray device: %s\n", device);
        return STREAM_UNSUPPORTED;
    }
    b->bd = bd;

    if (!check_disc_info(s)) {
        destruct(b);
        return STREAM_UNSUPPORTED;
    }

    int title_guess = BLURAY_DEFAULT_TITLE;
    if (b->use_nav) {
        MP_FATAL(s, "BluRay menu support has been removed.\n");
        return STREAM_ERROR;
    } else {
        /* check for available titles on disc */
        b->num_titles = bd_get_titles(bd, TITLES_RELEVANT, 0);
        if (!b->num_titles) {
            MP_ERR(s, "Can't find any Blu-ray-compatible title here.\n");
            destruct(b);
            return STREAM_UNSUPPORTED;
        }

        MP_INFO(s, "List of available titles:\n");

        /* parse titles information */
        uint64_t max_duration = 0;
        for (int i = 0; i < b->num_titles; i++) {
            BLURAY_TITLE_INFO *ti = bd_get_title_info(bd, i, 0);
            if (!ti)
                continue;

            char *time = mp_format_time(ti->duration / 90000, false);
            MP_INFO(s, "idx: %3d duration: %s (playlist: %05d.mpls)\n",
                       i, time, ti->playlist);
            talloc_free(time);

            /* try to guess which title may contain the main movie */
            if (ti->duration > max_duration) {
                max_duration = ti->duration;
                title_guess = i;
            }

            bd_free_title_info(ti);
        }
    }

    // these should be set before any callback
    b->current_angle = -1;
    b->current_title = -1;

    // initialize libbluray event queue
    bd_get_event(bd, NULL);

    select_initial_title(s, title_guess);

    s->fill_buffer = bluray_stream_fill_buffer;
    s->close       = bluray_stream_close;
    s->control     = bluray_stream_control;
    s->priv        = b;
    s->demuxer     = "+disc";

    MP_VERBOSE(s, "Blu-ray successfully opened.\n");

    return STREAM_OK;
}