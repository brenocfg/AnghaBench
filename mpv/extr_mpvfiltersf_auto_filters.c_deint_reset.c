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
struct mp_filter {struct deint_priv* priv; } ;
struct deint_priv {int /*<<< orphan*/  sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_subfilter_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deint_reset(struct mp_filter *f)
{
    struct deint_priv *p = f->priv;

    mp_subfilter_reset(&p->sub);
}