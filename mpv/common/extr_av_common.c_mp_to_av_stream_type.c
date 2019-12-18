#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;

/* Variables and functions */
 int AVMEDIA_TYPE_AUDIO ; 
 int AVMEDIA_TYPE_SUBTITLE ; 
 int AVMEDIA_TYPE_UNKNOWN ; 
 int AVMEDIA_TYPE_VIDEO ; 
#define  STREAM_AUDIO 130 
#define  STREAM_SUB 129 
#define  STREAM_VIDEO 128 

enum AVMediaType mp_to_av_stream_type(int type)
{
    switch (type) {
    case STREAM_VIDEO: return AVMEDIA_TYPE_VIDEO;
    case STREAM_AUDIO: return AVMEDIA_TYPE_AUDIO;
    case STREAM_SUB:   return AVMEDIA_TYPE_SUBTITLE;
    default:           return AVMEDIA_TYPE_UNKNOWN;
    }
}