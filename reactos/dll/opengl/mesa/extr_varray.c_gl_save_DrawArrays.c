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
typedef  scalar_t__ GLsizei ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_LINES 137 
#define  GL_LINE_LOOP 136 
#define  GL_LINE_STRIP 135 
#define  GL_POINTS 134 
#define  GL_POLYGON 133 
#define  GL_QUADS 132 
#define  GL_QUAD_STRIP 131 
#define  GL_TRIANGLES 130 
#define  GL_TRIANGLE_FAN 129 
#define  GL_TRIANGLE_STRIP 128 
 scalar_t__ INSIDE_BEGIN_END (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_save_ArrayElement (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gl_save_Begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_save_End (int /*<<< orphan*/ *) ; 

void gl_save_DrawArrays( GLcontext *ctx,
                         GLenum mode, GLint first, GLsizei count )
{
   GLint i;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glDrawArrays" );
      return;
   }
   if (count<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glDrawArrays(count)" );
      return;
   }
   switch (mode) {
      case GL_POINTS:
      case GL_LINES:
      case GL_LINE_STRIP:
      case GL_LINE_LOOP:
      case GL_TRIANGLES:
      case GL_TRIANGLE_STRIP:
      case GL_TRIANGLE_FAN:
      case GL_QUADS:
      case GL_QUAD_STRIP:
      case GL_POLYGON:
         /* OK */
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glDrawArrays(mode)" );
         return;
   }


   /* Note: this will do compile AND execute if needed */
   gl_save_Begin( ctx, mode );
   for (i=0;i<count;i++) {
      gl_save_ArrayElement( ctx, first+i );
   }
   gl_save_End( ctx );
}