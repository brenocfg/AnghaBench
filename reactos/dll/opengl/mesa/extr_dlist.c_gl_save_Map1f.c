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
struct TYPE_8__ {int /*<<< orphan*/  (* Map1f ) (TYPE_3__*,int /*<<< orphan*/ ,void*,void*,void*,void*,void* const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_1__ Exec; scalar_t__ ExecuteFlag; } ;
struct TYPE_9__ {void* data; void* i; void* f; int /*<<< orphan*/  e; } ;
typedef  TYPE_2__ Node ;
typedef  void* GLint ;
typedef  void* GLfloat ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_3__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  OPCODE_MAP1 ; 
 TYPE_2__* alloc_instruction (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,void*,void*,void*,void*,void* const*,int /*<<< orphan*/ ) ; 

void gl_save_Map1f( GLcontext *ctx,
                   GLenum target, GLfloat u1, GLfloat u2, GLint stride,
		   GLint order, const GLfloat *points, GLboolean retain )
{
   Node *n = alloc_instruction( ctx, OPCODE_MAP1, 6 );
   if (n) {
      n[1].e = target;
      n[2].f = u1;
      n[3].f = u2;
      n[4].i = stride;
      n[5].i = order;
      n[6].data = (void *) points;
   }
   if (ctx->ExecuteFlag) {
      (*ctx->Exec.Map1f)( ctx, target, u1, u2, stride, order, points, GL_TRUE );
   }
}