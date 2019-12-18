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
struct mp_imgfmt_desc {int /*<<< orphan*/  num_planes; int /*<<< orphan*/  id; } ;
struct mp_image_params {int /*<<< orphan*/  imgfmt; } ;
struct mp_image {struct mp_image_params params; int /*<<< orphan*/  num_planes; int /*<<< orphan*/  imgfmt; struct mp_imgfmt_desc fmt; } ;

/* Variables and functions */
 struct mp_imgfmt_desc mp_imgfmt_get_desc (int) ; 

void mp_image_setfmt(struct mp_image *mpi, int out_fmt)
{
    struct mp_image_params params = mpi->params;
    struct mp_imgfmt_desc fmt = mp_imgfmt_get_desc(out_fmt);
    params.imgfmt = fmt.id;
    mpi->fmt = fmt;
    mpi->imgfmt = fmt.id;
    mpi->num_planes = fmt.num_planes;
    mpi->params = params;
}