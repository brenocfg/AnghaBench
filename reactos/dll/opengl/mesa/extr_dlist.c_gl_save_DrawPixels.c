#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * data; void* e; void* i; } ;
typedef  TYPE_1__ Node ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  scalar_t__ GLsizei ;
typedef  void* GLint ;
typedef  void* GLenum ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_DRAW_PIXELS ; 
 TYPE_1__* alloc_instruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void gl_save_DrawPixels( GLcontext *ctx, GLsizei width, GLsizei height,
                         GLenum format, GLenum type, const GLvoid *pixels )
{
   Node *n = alloc_instruction( ctx, OPCODE_DRAW_PIXELS, 5 );
   if (n) {
      n[1].i = (GLint) width;
      n[2].i = (GLint) height;
      n[3].e = format;
      n[4].e = type;
      n[5].data = (GLvoid *) pixels;
   }
/* Special case:  gl_DrawPixels takes care of GL_COMPILE_AND_EXECUTE case!
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.DrawPixels)( ctx, width, height, format, type, pixels );
   }
*/
}