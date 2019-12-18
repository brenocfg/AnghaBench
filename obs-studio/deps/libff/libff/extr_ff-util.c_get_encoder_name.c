#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ff_format_desc {char const* name; } ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_3__ {char const* name; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 int AV_CODEC_ID_NONE ; 
 TYPE_1__* avcodec_find_encoder (int) ; 

__attribute__((used)) static const char *get_encoder_name(const struct ff_format_desc *format_desc,
                                    enum AVCodecID codec_id)
{
	AVCodec *codec = avcodec_find_encoder(codec_id);
	if (codec == NULL && codec_id == AV_CODEC_ID_NONE)
		return NULL;
	else if (codec == NULL)
		return format_desc->name;
	else
		return codec->name;
}