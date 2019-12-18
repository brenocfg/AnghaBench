#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct encoder_context {TYPE_2__* options; TYPE_1__* encoder; } ;
struct TYPE_4__ {double voffset; double aoffset; } ;
struct TYPE_3__ {int codec_type; } ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 

double encoder_get_offset(struct encoder_context *p)
{
    switch (p->encoder->codec_type) {
    case AVMEDIA_TYPE_VIDEO: return p->options->voffset;
    case AVMEDIA_TYPE_AUDIO: return p->options->aoffset;
    default:                 return 0;
    }
}