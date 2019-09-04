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
struct ra_gl {int /*<<< orphan*/  gl; scalar_t__ debug_enable; } ;
struct ra {int /*<<< orphan*/  log; struct ra_gl* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_check_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void gl_debug_marker(struct ra *ra, const char *msg)
{
    struct ra_gl *p = ra->priv;

    if (p->debug_enable)
        gl_check_error(p->gl, ra->log, msg);
}