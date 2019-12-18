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
struct ao_convert_fmt {int channels; int /*<<< orphan*/  src_fmt; } ;

/* Variables and functions */
 int af_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_plane (int,void*,int) ; 
 int get_conv_type (struct ao_convert_fmt*) ; 

void ao_convert_inplace(struct ao_convert_fmt *fmt, void **data, int num_samples)
{
    int type = get_conv_type(fmt);
    bool planar = af_fmt_is_planar(fmt->src_fmt);
    int planes = planar ? fmt->channels : 1;
    int plane_samples = num_samples * (planar ? 1: fmt->channels);
    for (int n = 0; n < planes; n++)
        convert_plane(type, data[n], plane_samples);
}