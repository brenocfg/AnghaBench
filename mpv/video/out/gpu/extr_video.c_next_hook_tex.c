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
struct ra_tex {int dummy; } ;
struct gl_video {scalar_t__ idx_hook_textures; scalar_t__ num_hook_textures; struct ra_tex** hook_textures; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct gl_video*,struct ra_tex**,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ra_tex **next_hook_tex(struct gl_video *p)
{
    if (p->idx_hook_textures == p->num_hook_textures)
        MP_TARRAY_APPEND(p, p->hook_textures, p->num_hook_textures, NULL);

    return &p->hook_textures[p->idx_hook_textures++];
}