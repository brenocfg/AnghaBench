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
struct mp_rect_f {int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
struct gl_transform {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_transform_vec (struct gl_transform,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gl_transform_rect(struct gl_transform t, struct mp_rect_f *r)
{
    gl_transform_vec(t, &r->x0, &r->y0);
    gl_transform_vec(t, &r->x1, &r->y1);
}