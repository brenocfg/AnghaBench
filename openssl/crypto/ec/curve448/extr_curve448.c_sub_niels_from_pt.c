#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* niels_t ;
typedef  int /*<<< orphan*/  gf ;
typedef  TYPE_2__* curve448_point_t ;
struct TYPE_6__ {int /*<<< orphan*/  t; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  z; } ;
struct TYPE_5__ {int /*<<< orphan*/  c; int /*<<< orphan*/  a; int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf_add_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_sub_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sub_niels_from_pt(curve448_point_t d, const niels_t e,
                              int before_double)
{
    gf a, b, c;

    gf_sub_nr(b, d->y, d->x);   /* 3+e */
    gf_mul(a, e->b, b);
    gf_add_nr(b, d->x, d->y);   /* 2+e */
    gf_mul(d->y, e->a, b);
    gf_mul(d->x, e->c, d->t);
    gf_add_nr(c, a, d->y);      /* 2+e */
    gf_sub_nr(b, d->y, a);      /* 3+e */
    gf_add_nr(d->y, d->z, d->x); /* 2+e */
    gf_sub_nr(a, d->z, d->x);   /* 3+e */
    gf_mul(d->z, a, d->y);
    gf_mul(d->x, d->y, b);
    gf_mul(d->y, a, c);
    if (!before_double)
        gf_mul(d->t, b, c);
}