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
struct ra_gl {int /*<<< orphan*/ * gl; } ;
struct ra {struct ra_gl* priv; } ;
typedef  int /*<<< orphan*/  GL ;

/* Variables and functions */

GL *ra_gl_get(struct ra *ra)
{
    struct ra_gl *p = ra->priv;
    return p->gl;
}