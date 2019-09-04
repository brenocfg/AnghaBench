#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct image {scalar_t__ type; scalar_t__ components; scalar_t__ multiplier; scalar_t__ w; scalar_t__ h; int /*<<< orphan*/  transform; TYPE_2__* tex; } ;
struct TYPE_3__ {scalar_t__ format; scalar_t__ w; scalar_t__ h; } ;
struct TYPE_4__ {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ gl_transform_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool image_equiv(struct image a, struct image b)
{
    return a.type == b.type &&
           a.components == b.components &&
           a.multiplier == b.multiplier &&
           a.tex->params.format == b.tex->params.format &&
           a.tex->params.w == b.tex->params.w &&
           a.tex->params.h == b.tex->params.h &&
           a.w == b.w &&
           a.h == b.h &&
           gl_transform_eq(a.transform, b.transform);
}