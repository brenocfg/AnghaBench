#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct stream_lang_req {int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct meta_dl {int /*<<< orphan*/ * di_name; } ;
struct bluray_priv_s {unsigned int const num_titles; unsigned int current_title; int current_angle; int /*<<< orphan*/  bd; TYPE_4__* title_info; } ;
struct TYPE_10__ {struct bluray_priv_s* priv; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_12__ {char* lang; int /*<<< orphan*/  pid; } ;
struct TYPE_11__ {unsigned int chapter_count; int angle_count; TYPE_2__* clips; int /*<<< orphan*/  clip_count; int /*<<< orphan*/  duration; TYPE_1__* chapters; } ;
struct TYPE_9__ {int audio_stream_count; int pg_stream_count; TYPE_5__* pg_streams; TYPE_5__* audio_streams; } ;
struct TYPE_8__ {int /*<<< orphan*/  start; } ;
typedef  TYPE_4__ BLURAY_TITLE_INFO ;
typedef  TYPE_5__ BLURAY_STREAM_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BD_TIME_FROM_MP (double) ; 
 double BD_TIME_TO_MP (int /*<<< orphan*/ ) ; 
 double MP_NOPTS_VALUE ; 
#define  STREAM_AUDIO 142 
#define  STREAM_CTRL_GET_ANGLE 141 
#define  STREAM_CTRL_GET_CHAPTER_TIME 140 
#define  STREAM_CTRL_GET_CURRENT_TIME 139 
#define  STREAM_CTRL_GET_CURRENT_TITLE 138 
#define  STREAM_CTRL_GET_DISC_NAME 137 
#define  STREAM_CTRL_GET_LANG 136 
#define  STREAM_CTRL_GET_NUM_ANGLES 135 
#define  STREAM_CTRL_GET_NUM_CHAPTERS 134 
#define  STREAM_CTRL_GET_NUM_TITLES 133 
#define  STREAM_CTRL_GET_TIME_LENGTH 132 
#define  STREAM_CTRL_SEEK_TO_TIME 131 
#define  STREAM_CTRL_SET_ANGLE 130 
#define  STREAM_CTRL_SET_CURRENT_TITLE 129 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
#define  STREAM_SUB 128 
 int STREAM_UNSUPPORTED ; 
 struct meta_dl* bd_get_meta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_seamless_angle_change (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bd_seek_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_tell_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  play_title (struct bluray_priv_s*,unsigned int const) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  stream_drop_buffers (TYPE_3__*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bluray_stream_control(stream_t *s, int cmd, void *arg)
{
    struct bluray_priv_s *b = s->priv;

    switch (cmd) {
    case STREAM_CTRL_GET_NUM_CHAPTERS: {
        const BLURAY_TITLE_INFO *ti = b->title_info;
        if (!ti)
            return STREAM_UNSUPPORTED;
        *((unsigned int *) arg) = ti->chapter_count;
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_CHAPTER_TIME: {
        const BLURAY_TITLE_INFO *ti = b->title_info;
        if (!ti)
            return STREAM_UNSUPPORTED;
        int chapter = *(double *)arg;
        double time = MP_NOPTS_VALUE;
        if (chapter >= 0 || chapter < ti->chapter_count)
            time = BD_TIME_TO_MP(ti->chapters[chapter].start);
        if (time == MP_NOPTS_VALUE)
            return STREAM_ERROR;
        *(double *)arg = time;
        return STREAM_OK;
    }
    case STREAM_CTRL_SET_CURRENT_TITLE: {
        const uint32_t title = *((unsigned int*)arg);
        if (title >= b->num_titles || !play_title(b, title))
            return STREAM_UNSUPPORTED;
        b->current_title = title;
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_CURRENT_TITLE: {
        *((unsigned int *) arg) = b->current_title;
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_NUM_TITLES: {
        *((unsigned int *)arg) = b->num_titles;
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_TIME_LENGTH: {
        const BLURAY_TITLE_INFO *ti = b->title_info;
        if (!ti)
            return STREAM_UNSUPPORTED;
        *((double *) arg) = BD_TIME_TO_MP(ti->duration);
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_CURRENT_TIME: {
        *((double *) arg) = BD_TIME_TO_MP(bd_tell_time(b->bd));
        return STREAM_OK;
    }
    case STREAM_CTRL_SEEK_TO_TIME: {
        double pts = *((double *) arg);
        bd_seek_time(b->bd, BD_TIME_FROM_MP(pts));
        stream_drop_buffers(s);
        // API makes it hard to determine seeking success
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_NUM_ANGLES: {
        const BLURAY_TITLE_INFO *ti = b->title_info;
        if (!ti)
            return STREAM_UNSUPPORTED;
        *((int *) arg) = ti->angle_count;
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_ANGLE: {
        *((int *) arg) = b->current_angle;
        return STREAM_OK;
    }
    case STREAM_CTRL_SET_ANGLE: {
        const BLURAY_TITLE_INFO *ti = b->title_info;
        if (!ti)
            return STREAM_UNSUPPORTED;
        int angle = *((int *) arg);
        if (angle < 0 || angle > ti->angle_count)
            return STREAM_UNSUPPORTED;
        b->current_angle = angle;
        bd_seamless_angle_change(b->bd, angle);
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_LANG: {
        const BLURAY_TITLE_INFO *ti = b->title_info;
        if (ti && ti->clip_count) {
            struct stream_lang_req *req = arg;
            BLURAY_STREAM_INFO *si = NULL;
            int count = 0;
            switch (req->type) {
            case STREAM_AUDIO:
                count = ti->clips[0].audio_stream_count;
                si = ti->clips[0].audio_streams;
                break;
            case STREAM_SUB:
                count = ti->clips[0].pg_stream_count;
                si = ti->clips[0].pg_streams;
                break;
            }
            for (int n = 0; n < count; n++) {
                BLURAY_STREAM_INFO *i = &si[n];
                if (i->pid == req->id) {
                    snprintf(req->name, sizeof(req->name), "%.4s", i->lang);
                    return STREAM_OK;
                }
            }
        }
        return STREAM_ERROR;
    }
    case STREAM_CTRL_GET_DISC_NAME: {
        const struct meta_dl *meta = bd_get_meta(b->bd);
        if (!meta || !meta->di_name || !meta->di_name[0])
            break;
        *(char**)arg = talloc_strdup(NULL, meta->di_name);
        return STREAM_OK;
    }
    default:
        break;
    }

    return STREAM_UNSUPPORTED;
}