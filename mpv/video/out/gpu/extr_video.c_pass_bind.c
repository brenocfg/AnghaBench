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
struct image {int dummy; } ;
struct gl_video {int num_pass_imgs; int /*<<< orphan*/  pass_imgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct gl_video*,int /*<<< orphan*/ ,int,struct image) ; 

__attribute__((used)) static int pass_bind(struct gl_video *p, struct image img)
{
    int idx = p->num_pass_imgs;
    MP_TARRAY_APPEND(p, p->pass_imgs, p->num_pass_imgs, img);
    return idx;
}