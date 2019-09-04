#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct stream_lang_req {int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct stream_dvd_info_req {int /*<<< orphan*/  palette; int /*<<< orphan*/  num_subs; } ;
struct TYPE_35__ {TYPE_10__* priv; } ;
typedef  TYPE_9__ stream_t ;
typedef  long long int64_t ;
struct TYPE_24__ {int cur_title; size_t dvd_title; int dvd_angle; int angle_seek; int /*<<< orphan*/  last_cell; TYPE_8__* cur_pgc; int /*<<< orphan*/  dvd; TYPE_6__* vmg_file; TYPE_11__* vts_file; TYPE_12__* tt_srpt; } ;
typedef  TYPE_10__ dvd_priv_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_34__ {TYPE_7__* cell_playback; int /*<<< orphan*/  palette; } ;
struct TYPE_33__ {long long last_sector; } ;
struct TYPE_32__ {TYPE_5__* tt_srpt; } ;
struct TYPE_31__ {unsigned int nr_of_srpts; TYPE_4__* title; } ;
struct TYPE_30__ {int nr_of_angles; } ;
struct TYPE_28__ {int /*<<< orphan*/  display_aspect_ratio; } ;
struct TYPE_29__ {TYPE_2__ vts_video_attr; } ;
struct TYPE_27__ {int /*<<< orphan*/  title_set_nr; } ;
struct TYPE_26__ {TYPE_1__* title; } ;
struct TYPE_25__ {TYPE_3__* vtsi_mat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVDISOVolumeInfo (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVDUDFVolumeInfo (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  STREAM_AUDIO 145 
#define  STREAM_CTRL_GET_ANGLE 144 
#define  STREAM_CTRL_GET_ASPECT_RATIO 143 
#define  STREAM_CTRL_GET_CHAPTER_TIME 142 
#define  STREAM_CTRL_GET_CURRENT_TIME 141 
#define  STREAM_CTRL_GET_CURRENT_TITLE 140 
#define  STREAM_CTRL_GET_DISC_NAME 139 
#define  STREAM_CTRL_GET_DVD_INFO 138 
#define  STREAM_CTRL_GET_LANG 137 
#define  STREAM_CTRL_GET_NUM_ANGLES 136 
#define  STREAM_CTRL_GET_NUM_CHAPTERS 135 
#define  STREAM_CTRL_GET_NUM_TITLES 134 
#define  STREAM_CTRL_GET_SIZE 133 
#define  STREAM_CTRL_GET_TIME_LENGTH 132 
#define  STREAM_CTRL_GET_TITLE_LENGTH 131 
#define  STREAM_CTRL_SEEK_TO_TIME 130 
#define  STREAM_CTRL_SET_ANGLE 129 
 int STREAM_OK ; 
#define  STREAM_SUB 128 
 int STREAM_UNSUPPORTED ; 
 double dvd_get_current_time (TYPE_9__*,int) ; 
 int dvd_lang_from_aid (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int dvd_lang_from_sid (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvd_number_of_subs (TYPE_9__*) ; 
 int /*<<< orphan*/  dvd_seek_to_time (TYPE_9__*,TYPE_11__*,double) ; 
 int get_chapter_time (TYPE_11__*,TYPE_12__*,int,double*) ; 
 int get_num_chapter (TYPE_11__*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct stream_dvd_info_req*,int /*<<< orphan*/ ,int) ; 
 double mp_get_titleset_length (TYPE_11__*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int control(stream_t *stream,int cmd,void* arg)
{
    dvd_priv_t *d = stream->priv;
    switch(cmd)
    {
        case STREAM_CTRL_GET_TIME_LENGTH:
        {
            *((double *)arg) = (double) mp_get_titleset_length(d->vts_file, d->tt_srpt, d->cur_title)/1000.0;
            return 1;
        }
        case STREAM_CTRL_GET_NUM_TITLES:
        {
            *((unsigned int *)arg) = d->vmg_file->tt_srpt->nr_of_srpts;
            return 1;
        }
        case STREAM_CTRL_GET_TITLE_LENGTH:
        {
            int t = *(double *)arg;
            if (t < 0 || t >= d->vmg_file->tt_srpt->nr_of_srpts)
                break;
            if (d->tt_srpt->title[t].title_set_nr !=
                d->tt_srpt->title[d->dvd_title].title_set_nr)
                break;
            *(double *)arg =
                mp_get_titleset_length(d->vts_file, d->tt_srpt, t) / 1000.0;
            return 1;
        }
        case STREAM_CTRL_GET_NUM_CHAPTERS:
        {
            int r;
            r = get_num_chapter(d->vts_file, d->tt_srpt, d->cur_title);
            if(! r) return STREAM_UNSUPPORTED;
            *((unsigned int *)arg) = r;
            return 1;
        }
        case STREAM_CTRL_GET_CHAPTER_TIME:
        {
            int r;
            r = get_chapter_time(d->vts_file, d->tt_srpt, d->cur_title, (double *)arg);
            if(! r) return STREAM_UNSUPPORTED;
            return 1;
        }
        case STREAM_CTRL_GET_CURRENT_TITLE:
        {
            *((unsigned int *)arg) = d->cur_title;
            return 1;
        }
        case STREAM_CTRL_GET_CURRENT_TIME:
        {
            double tm;
            tm = dvd_get_current_time(stream, -1);
            if(tm != -1) {
              *((double *)arg) = tm;
              return 1;
            }
            break;
        }
        case STREAM_CTRL_SEEK_TO_TIME:
        {
            if(dvd_seek_to_time(stream, d->vts_file, *((double*)arg)))
              return 1;
            break;
        }
        case STREAM_CTRL_GET_ASPECT_RATIO:
        {
            *((double *)arg) = !d->vts_file->vtsi_mat->vts_video_attr.display_aspect_ratio ? 4.0/3.0 : 16.0/9.0;
            return 1;
        }
        case STREAM_CTRL_GET_NUM_ANGLES:
        {
            *((int *)arg) = d->vmg_file->tt_srpt->title[d->dvd_title].nr_of_angles;
            return 1;
        }
        case STREAM_CTRL_GET_ANGLE:
        {
            *((int *)arg) = d->dvd_angle;
            return 1;
        }
        case STREAM_CTRL_SET_ANGLE:
        {
            int ang = *((int *)arg);
            if(ang>d->vmg_file->tt_srpt->title[d->dvd_title].nr_of_angles || ang<=0)
                break;
            d->dvd_angle = ang;
            d->angle_seek = 1;
            return 1;
        }
        case STREAM_CTRL_GET_LANG:
        {
            struct stream_lang_req *req = arg;
            int lang = 0;
            switch(req->type) {
            case STREAM_AUDIO:
                lang = dvd_lang_from_aid(stream, req->id);
                break;
            case STREAM_SUB:
                lang = dvd_lang_from_sid(stream, req->id);
                break;
            }
            if (!lang)
                break;
            snprintf(req->name, sizeof(req->name), "%c%c", lang >> 8, lang);
            return STREAM_OK;
        }
        case STREAM_CTRL_GET_DVD_INFO:
        {
            struct stream_dvd_info_req *req = arg;
            memset(req, 0, sizeof(*req));
            req->num_subs = dvd_number_of_subs(stream);
            memcpy(req->palette, d->cur_pgc->palette, sizeof(req->palette));
            return STREAM_OK;
        }
        case STREAM_CTRL_GET_DISC_NAME:
        {
            char buffer[128];
            if (DVDUDFVolumeInfo(d->dvd, buffer, sizeof(buffer), NULL, 0) < 0 &&
                DVDISOVolumeInfo(d->dvd, buffer, sizeof(buffer), NULL, 0) < 0)
                break;
            if (!buffer[0])
                break;
            *(char**)arg = talloc_strdup(NULL, buffer);
            return STREAM_OK;
        }
        case STREAM_CTRL_GET_SIZE:
            *(int64_t *)arg =
                (d->cur_pgc->cell_playback[d->last_cell-1].last_sector)*2048LL;
            return STREAM_OK;
    }
    return STREAM_UNSUPPORTED;
}