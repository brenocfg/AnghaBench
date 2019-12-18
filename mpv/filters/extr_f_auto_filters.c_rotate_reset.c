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
struct rotate_priv {int /*<<< orphan*/  sub; } ;
struct mp_filter {struct rotate_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_subfilter_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rotate_reset(struct mp_filter *f)
{
    struct rotate_priv *p = f->priv;

    mp_subfilter_reset(&p->sub);
}