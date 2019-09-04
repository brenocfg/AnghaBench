#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int w; int h; } ;
struct mp_image {int w; int h; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void mp_image_set_size(struct mp_image *mpi, int w, int h)
{
    assert(w >= 0 && h >= 0);
    mpi->w = mpi->params.w = w;
    mpi->h = mpi->params.h = h;
}