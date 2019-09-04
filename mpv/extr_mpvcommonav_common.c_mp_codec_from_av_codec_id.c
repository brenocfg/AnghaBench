#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {char* name; } ;
typedef  TYPE_1__ AVCodecDescriptor ;
typedef  TYPE_2__ AVCodec ;

/* Variables and functions */
 TYPE_1__* avcodec_descriptor_get (int) ; 
 TYPE_2__* avcodec_find_decoder (int) ; 

const char *mp_codec_from_av_codec_id(int codec_id)
{
    const char *name = NULL;
    const AVCodecDescriptor *desc = avcodec_descriptor_get(codec_id);
    if (desc)
        name = desc->name;
    if (!name) {
        AVCodec *avcodec = avcodec_find_decoder(codec_id);
        if (avcodec)
            name = avcodec->name;
    }
    return name;
}