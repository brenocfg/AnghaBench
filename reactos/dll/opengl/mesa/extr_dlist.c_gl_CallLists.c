#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ListBase; } ;
struct TYPE_6__ {int /*<<< orphan*/  CompileFlag; TYPE_1__ List; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLsizei ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  execute_list (TYPE_2__*,scalar_t__) ; 
 scalar_t__ translate_id (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void gl_CallLists( GLcontext *ctx,
                   GLsizei n, GLenum type, const GLvoid *lists )
{
   GLuint i, list;
   GLboolean save_compile_flag;

   /* Save the CompileFlag status, turn it off, execute display list,
    * and restore the CompileFlag.
    */
   save_compile_flag = ctx->CompileFlag;
   ctx->CompileFlag = GL_FALSE;

   for (i=0;i<n;i++) {
      list = translate_id( i, type, lists );
      execute_list( ctx, ctx->List.ListBase + list );
   }

   ctx->CompileFlag = save_compile_flag;
}