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
struct TYPE_3__ {char const* name; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 TYPE_1__* avcodec_find_encoder (int) ; 

const char *ff_codec_name_from_id(int codec_id)
{
	AVCodec *codec = avcodec_find_encoder(codec_id);
	if (codec != NULL)
		return codec->name;
	else
		return NULL;
}