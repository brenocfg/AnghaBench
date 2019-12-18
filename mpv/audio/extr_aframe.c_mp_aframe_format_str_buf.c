#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num; } ;
struct mp_aframe {int /*<<< orphan*/  format; TYPE_2__ chmap; TYPE_1__* av_frame; } ;
typedef  int /*<<< orphan*/  ch ;
struct TYPE_4__ {int sample_rate; } ;

/* Variables and functions */
 char* af_fmt_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_to_str_buf (char*,int,TYPE_2__*) ; 
 char* mp_chmap_to_str_hr (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_snprintf_cat (char*,int,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,char*,int,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

char *mp_aframe_format_str_buf(char *buf, size_t buf_size, struct mp_aframe *fmt)
{
    char ch[128];
    mp_chmap_to_str_buf(ch, sizeof(ch), &fmt->chmap);
    char *hr_ch = mp_chmap_to_str_hr(&fmt->chmap);
    if (strcmp(hr_ch, ch) != 0)
        mp_snprintf_cat(ch, sizeof(ch), " (%s)", hr_ch);
    snprintf(buf, buf_size, "%dHz %s %dch %s", fmt->av_frame->sample_rate,
             ch, fmt->chmap.num, af_fmt_to_str(fmt->format));
    return buf;
}