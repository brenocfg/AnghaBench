#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pniels_t ;
typedef  TYPE_3__* curve448_point_t ;
struct TYPE_8__ {int /*<<< orphan*/  z; int /*<<< orphan*/  t; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int /*<<< orphan*/  z; TYPE_1__* n; } ;
struct TYPE_6__ {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 int TWISTED_D ; 
 int /*<<< orphan*/  gf_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_mulw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gf_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt_to_pniels(pniels_t b, const curve448_point_t a)
{
    gf_sub(b->n->a, a->y, a->x);
    gf_add(b->n->b, a->x, a->y);
    gf_mulw(b->n->c, a->t, 2 * TWISTED_D);
    gf_add(b->z, a->z, a->z);
}