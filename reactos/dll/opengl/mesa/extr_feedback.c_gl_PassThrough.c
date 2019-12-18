#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ RenderMode; } ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDBACK_TOKEN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GL_FEEDBACK ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ GL_PASS_THROUGH_TOKEN ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_1__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

void gl_PassThrough( GLcontext *ctx, GLfloat token )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glPassThrough" );
      return;
   }

   if (ctx->RenderMode==GL_FEEDBACK) {
      FEEDBACK_TOKEN( ctx, (GLfloat) (GLint) GL_PASS_THROUGH_TOKEN );
      FEEDBACK_TOKEN( ctx, token );
   }
}