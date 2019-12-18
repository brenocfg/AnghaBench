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
struct mp_image_params {int w; int h; int p_w; int p_h; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int MPCLAMP (int,int,int /*<<< orphan*/ ) ; 

void mp_image_params_get_dsize(const struct mp_image_params *p,
                               int *d_w, int *d_h)
{
    *d_w = p->w;
    *d_h = p->h;
    if (p->p_w > p->p_h && p->p_h >= 1)
        *d_w = MPCLAMP(*d_w * (int64_t)p->p_w / p->p_h, 1, INT_MAX);
    if (p->p_h > p->p_w && p->p_w >= 1)
        *d_h = MPCLAMP(*d_h * (int64_t)p->p_h / p->p_w, 1, INT_MAX);
}