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
struct ra_format {int /*<<< orphan*/  name; } ;
struct gl_video {int /*<<< orphan*/  ra; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct gl_video*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,struct ra_tex**) ; 
 int ra_tex_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ra_tex**,int,int,struct ra_format const*) ; 

__attribute__((used)) static bool test_fbo(struct gl_video *p, const struct ra_format *fmt)
{
    MP_VERBOSE(p, "Testing FBO format %s\n", fmt->name);
    struct ra_tex *tex = NULL;
    bool success = ra_tex_resize(p->ra, p->log, &tex, 16, 16, fmt);
    ra_tex_free(p->ra, &tex);
    return success;
}