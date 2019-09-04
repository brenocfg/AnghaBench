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
struct priv {int /*<<< orphan*/  lavc_actx; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset (struct mp_filter*) ; 

__attribute__((used)) static void destroy(struct mp_filter *f)
{
    struct priv *s = f->priv;

    reset(f);
    avcodec_free_context(&s->lavc_actx);
}