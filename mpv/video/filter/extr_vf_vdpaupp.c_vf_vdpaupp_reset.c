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
struct priv {int /*<<< orphan*/  queue; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_refqueue_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vf_vdpaupp_reset(struct mp_filter *f)
{
    struct priv *p = f->priv;
    mp_refqueue_flush(p->queue);
}