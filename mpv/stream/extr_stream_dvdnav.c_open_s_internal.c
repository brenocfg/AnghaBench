#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct priv {char* device; scalar_t__ track; scalar_t__ title; TYPE_4__* opts; int /*<<< orphan*/ * dvdnav; } ;
struct TYPE_10__ {char* demuxer; char* lavf_type; int /*<<< orphan*/  close; int /*<<< orphan*/  control; int /*<<< orphan*/  fill_buffer; int /*<<< orphan*/  global; struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dvdnav_t ;
struct TYPE_11__ {char* device; int angle; } ;

/* Variables and functions */
 char* DEFAULT_DVD_DEVICE ; 
 scalar_t__ DVDNAV_STATUS_OK ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  MP_FATAL (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  MP_INFO (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*,...) ; 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 scalar_t__ TITLE_LONGEST ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  dvd_conf ; 
 int /*<<< orphan*/  dvdnav_angle_change (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dvdnav_describe_title_chapters (int /*<<< orphan*/ *,int,int**,int*) ; 
 int /*<<< orphan*/  dvdnav_err_to_string (int /*<<< orphan*/ *) ; 
 scalar_t__ dvdnav_get_number_of_titles (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ dvdnav_title_play (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fill_buffer ; 
 int /*<<< orphan*/  free (int*) ; 
 char* mp_format_time (int,int) ; 
 TYPE_4__* mp_get_config_group (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_dvdnav_stream (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stream_dvdnav_close ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int open_s_internal(stream_t *stream)
{
    struct priv *priv, *p;
    priv = p = stream->priv;
    char *filename;

    p->opts = mp_get_config_group(stream, stream->global, &dvd_conf);

    if (p->device && p->device[0])
        filename = p->device;
    else if (p->opts->device && p->opts->device[0])
        filename = p->opts->device;
    else
        filename = DEFAULT_DVD_DEVICE;
    if (!new_dvdnav_stream(stream, filename)) {
        MP_ERR(stream, "Couldn't open DVD device: %s\n",
                filename);
        return STREAM_UNSUPPORTED;
    }

    if (p->track == TITLE_LONGEST) { // longest
        dvdnav_t *dvdnav = priv->dvdnav;
        uint64_t best_length = 0;
        int best_title = -1;
        int32_t num_titles;
        if (dvdnav_get_number_of_titles(dvdnav, &num_titles) == DVDNAV_STATUS_OK) {
            MP_VERBOSE(stream, "List of available titles:\n");
            for (int n = 1; n <= num_titles; n++) {
                uint64_t *parts = NULL, duration = 0;
                dvdnav_describe_title_chapters(dvdnav, n, &parts, &duration);
                if (parts) {
                    if (duration > best_length) {
                        best_length = duration;
                        best_title = n;
                    }
                    if (duration > 90000) { // arbitrarily ignore <1s titles
                        char *time = mp_format_time(duration / 90000, false);
                        MP_VERBOSE(stream, "title: %3d duration: %s\n",
                                   n - 1, time);
                        talloc_free(time);
                    }
                    free(parts);
                }
            }
        }
        p->track = best_title - 1;
        MP_INFO(stream, "Selecting title %d.\n", p->track);
    }

    if (p->track >= 0) {
        priv->title = p->track;
        if (dvdnav_title_play(priv->dvdnav, p->track + 1) != DVDNAV_STATUS_OK) {
            MP_FATAL(stream, "dvdnav_stream, couldn't select title %d, error '%s'\n",
                   p->track, dvdnav_err_to_string(priv->dvdnav));
            return STREAM_UNSUPPORTED;
        }
    } else {
        MP_FATAL(stream, "DVD menu support has been removed.\n");
        return STREAM_ERROR;
    }
    if (p->opts->angle > 1)
        dvdnav_angle_change(priv->dvdnav, p->opts->angle);

    stream->fill_buffer = fill_buffer;
    stream->control = control;
    stream->close = stream_dvdnav_close;
    stream->demuxer = "+disc";
    stream->lavf_type = "mpeg";

    return STREAM_OK;
}