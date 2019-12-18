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
struct TYPE_8__ {int /*<<< orphan*/  (* CopyTexImage1D ) (TYPE_3__*,void*,void*,void*,void*,void*,void*,void*) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {void* i; void* e; } ;
typedef  TYPE_2__ Node ;
typedef  void* GLsizei ;
typedef  void* GLint ;
typedef  void* GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_COPY_TEX_IMAGE1D ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,void*,void*,void*,void*,void*) ; 

void gl_save_CopyTexImage1D( GLcontext *ctx,
                             GLenum target, GLint level,
                             GLenum internalformat,
                             GLint x, GLint y, GLsizei width,
                             GLint border )
{
   Node *n = alloc_instruction( ctx, OPCODE_COPY_TEX_IMAGE1D, 7 );
   if (n) {
      n[1].e = target;
      n[2].i = level;
      n[3].e = internalformat;
      n[4].i = x;
      n[5].i = y;
      n[6].i = width;
      n[7].i = border;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.CopyTexImage1D)( ctx, target, level, internalformat,
                            x, y, width, border );
   }
}