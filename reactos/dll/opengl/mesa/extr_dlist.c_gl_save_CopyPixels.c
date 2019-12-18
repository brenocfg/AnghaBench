#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* CopyPixels ) (TYPE_3__*,void*,void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {int /*<<< orphan*/  e; void* i; } ;
typedef  TYPE_2__ Node ;
typedef  scalar_t__ GLsizei ;
typedef  void* GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_COPY_PIXELS ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void gl_save_CopyPixels( GLcontext *ctx, GLint x, GLint y,
			 GLsizei width, GLsizei height, GLenum type )
{
   Node *n = alloc_instruction( ctx, OPCODE_COPY_PIXELS, 5 );
   if (n) {
      n[1].i = x;
      n[2].i = y;
      n[3].i = (GLint) width;
      n[4].i = (GLint) height;
      n[5].e = type;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.CopyPixels)( ctx, x, y, width, height, type );
   }
}