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
struct gl_video {int /*<<< orphan*/  ra; void* osd_timer; void* blit_timer; void* upload_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGL_DEBUG ; 
 int /*<<< orphan*/  debug_check_gl (struct gl_video*,char*) ; 
 int /*<<< orphan*/  ra_dump_img_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_dump_tex_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* timer_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_gl(struct gl_video *p)
{
    debug_check_gl(p, "before init_gl");

    p->upload_timer = timer_pool_create(p->ra);
    p->blit_timer = timer_pool_create(p->ra);
    p->osd_timer = timer_pool_create(p->ra);

    debug_check_gl(p, "after init_gl");

    ra_dump_tex_formats(p->ra, MSGL_DEBUG);
    ra_dump_img_formats(p->ra, MSGL_DEBUG);
}