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
struct ra_renderpass {struct d3d_rpass* priv; } ;
struct ra {int dummy; } ;
struct d3d_rpass {int /*<<< orphan*/  bstate; int /*<<< orphan*/  layout; int /*<<< orphan*/  cs; int /*<<< orphan*/  ps; int /*<<< orphan*/  vs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct ra_renderpass*) ; 

__attribute__((used)) static void renderpass_destroy(struct ra *ra, struct ra_renderpass *pass)
{
    if (!pass)
        return;
    struct d3d_rpass *pass_p = pass->priv;

    SAFE_RELEASE(pass_p->vs);
    SAFE_RELEASE(pass_p->ps);
    SAFE_RELEASE(pass_p->cs);
    SAFE_RELEASE(pass_p->layout);
    SAFE_RELEASE(pass_p->bstate);
    talloc_free(pass);
}