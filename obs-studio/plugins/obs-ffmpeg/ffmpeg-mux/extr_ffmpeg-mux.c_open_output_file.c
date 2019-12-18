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
struct TYPE_7__ {char* file; char* muxer_settings; } ;
struct ffmpeg_mux {TYPE_1__ params; TYPE_4__* output; } ;
struct TYPE_10__ {scalar_t__* filename; int /*<<< orphan*/  pb; TYPE_2__* oformat; } ;
struct TYPE_9__ {char* key; char* value; } ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ AVOutputFormat ;
typedef  TYPE_3__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int FFM_ERROR ; 
 int FFM_SUCCESS ; 
 int FFM_UNSUPPORTED ; 
 scalar_t__ av_dict_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int av_dict_parse_string (int /*<<< orphan*/ **,char*,char*,char*,int /*<<< orphan*/ ) ; 
 char* av_err2str (int) ; 
 int avformat_write_header (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int avio_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char*,int) ; 

__attribute__((used)) static inline int open_output_file(struct ffmpeg_mux *ffm)
{
	AVOutputFormat *format = ffm->output->oformat;
	int ret;

	if ((format->flags & AVFMT_NOFILE) == 0) {
		ret = avio_open(&ffm->output->pb, ffm->params.file,
				AVIO_FLAG_WRITE);
		if (ret < 0) {
			fprintf(stderr, "Couldn't open '%s', %s",
				ffm->params.file, av_err2str(ret));
			return FFM_ERROR;
		}
	}

	strncpy(ffm->output->filename, ffm->params.file,
		sizeof(ffm->output->filename));
	ffm->output->filename[sizeof(ffm->output->filename) - 1] = 0;

	AVDictionary *dict = NULL;
	if ((ret = av_dict_parse_string(&dict, ffm->params.muxer_settings, "=",
					" ", 0))) {
		fprintf(stderr, "Failed to parse muxer settings: %s\n%s",
			av_err2str(ret), ffm->params.muxer_settings);

		av_dict_free(&dict);
	}

	if (av_dict_count(dict) > 0) {
		printf("Using muxer settings:");

		AVDictionaryEntry *entry = NULL;
		while ((entry = av_dict_get(dict, "", entry,
					    AV_DICT_IGNORE_SUFFIX)))
			printf("\n\t%s=%s", entry->key, entry->value);

		printf("\n");
	}

	ret = avformat_write_header(ffm->output, &dict);
	if (ret < 0) {
		fprintf(stderr, "Error opening '%s': %s", ffm->params.file,
			av_err2str(ret));

		av_dict_free(&dict);

		return ret == -22 ? FFM_UNSUPPORTED : FFM_ERROR;
	}

	av_dict_free(&dict);

	return FFM_SUCCESS;
}