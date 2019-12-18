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
struct mp_image {int /*<<< orphan*/ * bufs; scalar_t__* stride; int /*<<< orphan*/ ** planes; } ;

/* Variables and functions */
 int MP_MAX_PLANES ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

void mp_image_unref_data(struct mp_image *img)
{
    for (int n = 0; n < MP_MAX_PLANES; n++) {
        img->planes[n] = NULL;
        img->stride[n] = 0;
        av_buffer_unref(&img->bufs[n]);
    }
}