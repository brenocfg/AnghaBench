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
struct mp_image {int num_planes; int* stride; scalar_t__* planes; } ;

/* Variables and functions */
 int mp_image_plane_h (struct mp_image*,int) ; 

void mp_image_vflip(struct mp_image *img)
{
    for (int p = 0; p < img->num_planes; p++) {
        int plane_h = mp_image_plane_h(img, p);
        img->planes[p] = img->planes[p] + img->stride[p] * (plane_h - 1);
        img->stride[p] = -img->stride[p];
    }
}