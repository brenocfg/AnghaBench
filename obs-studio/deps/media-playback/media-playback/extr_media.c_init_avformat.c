#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  path; void* has_audio; void* has_video; int /*<<< orphan*/  hw; TYPE_5__* fmt; int /*<<< orphan*/  buffering; int /*<<< orphan*/  is_local_file; scalar_t__* format_name; } ;
typedef  TYPE_2__ mp_media_t ;
struct TYPE_8__ {TYPE_2__* opaque; int /*<<< orphan*/  callback; } ;
struct TYPE_10__ {TYPE_1__ interrupt_callback; } ;
typedef  int /*<<< orphan*/  AVInputFormat ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_find_input_format (scalar_t__*) ; 
 TYPE_5__* avformat_alloc_context () ; 
 scalar_t__ avformat_find_stream_info (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int avformat_open_input (TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interrupt_callback ; 
 void* mp_decode_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool init_avformat(mp_media_t *m)
{
	AVInputFormat *format = NULL;

	if (m->format_name && *m->format_name) {
		format = av_find_input_format(m->format_name);
		if (!format)
			blog(LOG_INFO,
			     "MP: Unable to find input format for "
			     "'%s'",
			     m->path);
	}

	AVDictionary *opts = NULL;
	if (m->buffering && !m->is_local_file)
		av_dict_set_int(&opts, "buffer_size", m->buffering, 0);

	m->fmt = avformat_alloc_context();
	m->fmt->interrupt_callback.callback = interrupt_callback;
	m->fmt->interrupt_callback.opaque = m;

	int ret = avformat_open_input(&m->fmt, m->path, format,
				      opts ? &opts : NULL);
	av_dict_free(&opts);

	if (ret < 0) {
		blog(LOG_WARNING, "MP: Failed to open media: '%s'", m->path);
		return false;
	}

	if (avformat_find_stream_info(m->fmt, NULL) < 0) {
		blog(LOG_WARNING, "MP: Failed to find stream info for '%s'",
		     m->path);
		return false;
	}

	m->has_video = mp_decode_init(m, AVMEDIA_TYPE_VIDEO, m->hw);
	m->has_audio = mp_decode_init(m, AVMEDIA_TYPE_AUDIO, m->hw);

	if (!m->has_video && !m->has_audio) {
		blog(LOG_WARNING,
		     "MP: Could not initialize audio or video: "
		     "'%s'",
		     m->path);
		return false;
	}

	return true;
}