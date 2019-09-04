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
struct TYPE_5__ {int /*<<< orphan*/  mf; } ;
struct TYPE_6__ {int /*<<< orphan*/  operation; TYPE_1__ number; } ;
typedef  TYPE_2__ calc_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int /*<<< orphan*/  mpfr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void node_copy(calc_node_t *dst, calc_node_t *src)
{
    mpfr_set(dst->number.mf, src->number.mf, MPFR_DEFAULT_RND);
    dst->operation = src->operation;
}