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
struct ra_fbo {int dummy; } ;
struct mp_rect {int dummy; } ;
struct gl_video {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_binds (struct gl_video*) ; 
 int /*<<< orphan*/  debug_check_gl (struct gl_video*,char*) ; 
 int /*<<< orphan*/  pass_prepare_src_tex (struct gl_video*) ; 
 int /*<<< orphan*/  pass_record (struct gl_video*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_pass_quad (struct gl_video*,struct ra_fbo,int,struct mp_rect const*) ; 

__attribute__((used)) static void finish_pass_fbo(struct gl_video *p, struct ra_fbo fbo,
                            bool discard, const struct mp_rect *dst)
{
    pass_prepare_src_tex(p);
    pass_record(p, render_pass_quad(p, fbo, discard, dst));
    debug_check_gl(p, "after rendering");
    cleanup_binds(p);
}