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
struct gl_image {int dummy; } ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  gl_problem (int /*<<< orphan*/ *,char*) ; 

void gl_ColorSubTable( GLcontext *ctx, GLenum target,
                       GLsizei start, struct gl_image *data )
{
   /* XXX TODO */
   gl_problem(ctx, "glColorSubTableEXT not implemented");
}