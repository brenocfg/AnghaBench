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
struct mp_filter {struct deint_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  filter; } ;
struct deint_priv {TYPE_1__ sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_subfilter_reset (TYPE_1__*) ; 

__attribute__((used)) static void deint_destroy(struct mp_filter *f)
{
    struct deint_priv *p = f->priv;

    mp_subfilter_reset(&p->sub);
    TA_FREEP(&p->sub.filter);
}