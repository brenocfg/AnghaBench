#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ffmpeg_decode {TYPE_1__* decoder; TYPE_2__* codec; } ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_7__ {int capabilities; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int CODEC_CAP_TRUNC ; 
 int /*<<< orphan*/  CODEC_FLAG_TRUNC ; 
 TYPE_1__* avcodec_alloc_context3 (TYPE_2__*) ; 
 TYPE_2__* avcodec_find_decoder (int) ; 
 int avcodec_open2 (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_register_all () ; 
 int /*<<< orphan*/  ffmpeg_decode_free (struct ffmpeg_decode*) ; 
 int /*<<< orphan*/  memset (struct ffmpeg_decode*,int /*<<< orphan*/ ,int) ; 

int ffmpeg_decode_init(struct ffmpeg_decode *decode, enum AVCodecID id)
{
	int ret;

	avcodec_register_all();
	memset(decode, 0, sizeof(*decode));

	decode->codec = avcodec_find_decoder(id);
	if (!decode->codec)
		return -1;

	decode->decoder = avcodec_alloc_context3(decode->codec);

	ret = avcodec_open2(decode->decoder, decode->codec, NULL);
	if (ret < 0) {
		ffmpeg_decode_free(decode);
		return ret;
	}

	if (decode->codec->capabilities & CODEC_CAP_TRUNC)
		decode->decoder->flags |= CODEC_FLAG_TRUNC;

	return 0;
}