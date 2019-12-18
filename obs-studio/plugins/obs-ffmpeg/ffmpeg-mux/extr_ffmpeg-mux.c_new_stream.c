#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ffmpeg_mux {TYPE_5__* output; } ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_9__ {scalar_t__ nb_streams; } ;
struct TYPE_8__ {int id; } ;
struct TYPE_7__ {scalar_t__ id; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVCodecDescriptor ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 TYPE_2__* avcodec_descriptor_get_by_name (char const*) ; 
 int /*<<< orphan*/ * avcodec_find_encoder (int) ; 
 TYPE_1__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool new_stream(struct ffmpeg_mux *ffm, AVStream **stream,
		       const char *name, enum AVCodecID *id)
{
	const AVCodecDescriptor *desc = avcodec_descriptor_get_by_name(name);
	AVCodec *codec;

	if (!desc) {
		fprintf(stderr, "Couldn't find encoder '%s'\n", name);
		return false;
	}

	*id = desc->id;

	codec = avcodec_find_encoder(desc->id);
	if (!codec) {
		fprintf(stderr, "Couldn't create encoder");
		return false;
	}

	*stream = avformat_new_stream(ffm->output, codec);
	if (!*stream) {
		fprintf(stderr, "Couldn't create stream for encoder '%s'\n",
			name);
		return false;
	}

	(*stream)->id = ffm->output->nb_streams - 1;
	return true;
}