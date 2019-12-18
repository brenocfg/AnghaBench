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
struct mp_image {struct AVBufferRef** bufs; } ;
struct AVBufferRef {scalar_t__ size; } ;

/* Variables and functions */
 int MP_MAX_PLANES ; 

int mp_image_approx_byte_size(struct mp_image *img)
{
    int total = sizeof(*img);

    for (int n = 0; n < MP_MAX_PLANES; n++) {
        struct AVBufferRef *buf = img->bufs[n];
        if (buf)
            total += buf->size;
    }

    return total;
}