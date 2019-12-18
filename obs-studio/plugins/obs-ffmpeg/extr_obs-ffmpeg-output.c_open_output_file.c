#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  url; int /*<<< orphan*/  muxer_settings; } ;
struct ffmpeg_data {TYPE_1__ config; TYPE_4__* output; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {scalar_t__* filename; int /*<<< orphan*/  pb; TYPE_2__* oformat; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ AVOutputFormat ;
typedef  TYPE_3__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ av_dict_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int av_dict_parse_string (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int avformat_write_header (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int avio_open2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_catf (struct dstr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  ffmpeg_log_error (int /*<<< orphan*/ ,struct ffmpeg_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool open_output_file(struct ffmpeg_data *data)
{
	AVOutputFormat *format = data->output->oformat;
	int ret;

	AVDictionary *dict = NULL;
	if ((ret = av_dict_parse_string(&dict, data->config.muxer_settings, "=",
					" ", 0))) {
		ffmpeg_log_error(LOG_WARNING, data,
				 "Failed to parse muxer settings: %s\n%s",
				 av_err2str(ret), data->config.muxer_settings);

		av_dict_free(&dict);
		return false;
	}

	if (av_dict_count(dict) > 0) {
		struct dstr str = {0};

		AVDictionaryEntry *entry = NULL;
		while ((entry = av_dict_get(dict, "", entry,
					    AV_DICT_IGNORE_SUFFIX)))
			dstr_catf(&str, "\n\t%s=%s", entry->key, entry->value);

		blog(LOG_INFO, "Using muxer settings: %s", str.array);
		dstr_free(&str);
	}

	if ((format->flags & AVFMT_NOFILE) == 0) {
		ret = avio_open2(&data->output->pb, data->config.url,
				 AVIO_FLAG_WRITE, NULL, &dict);
		if (ret < 0) {
			ffmpeg_log_error(LOG_WARNING, data,
					 "Couldn't open '%s', %s",
					 data->config.url, av_err2str(ret));
			av_dict_free(&dict);
			return false;
		}
	}

	strncpy(data->output->filename, data->config.url,
		sizeof(data->output->filename));
	data->output->filename[sizeof(data->output->filename) - 1] = 0;

	ret = avformat_write_header(data->output, &dict);
	if (ret < 0) {
		ffmpeg_log_error(LOG_WARNING, data, "Error opening '%s': %s",
				 data->config.url, av_err2str(ret));
		return false;
	}

	if (av_dict_count(dict) > 0) {
		struct dstr str = {0};

		AVDictionaryEntry *entry = NULL;
		while ((entry = av_dict_get(dict, "", entry,
					    AV_DICT_IGNORE_SUFFIX)))
			dstr_catf(&str, "\n\t%s=%s", entry->key, entry->value);

		blog(LOG_INFO, "Invalid muxer settings: %s", str.array);
		dstr_free(&str);
	}

	av_dict_free(&dict);

	return true;
}