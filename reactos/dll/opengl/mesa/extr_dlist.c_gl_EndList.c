#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Exec; int /*<<< orphan*/  API; int /*<<< orphan*/  CompileFlag; int /*<<< orphan*/  ExecuteFlag; int /*<<< orphan*/ * CurrentListPtr; scalar_t__ CurrentListNum; TYPE_1__* Shared; } ;
struct TYPE_7__ {int /*<<< orphan*/  DisplayList; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  HashInsert (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPCODE_END_OF_LIST ; 
 int /*<<< orphan*/ * alloc_instruction (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_destroy_list (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_EndList( GLcontext *ctx )
{
   Node *n;

   /* Check that a list is under construction */
   if (!ctx->CurrentListPtr) {
      gl_error( ctx, GL_INVALID_OPERATION, "glEndList" );
      return;
   }

   n = alloc_instruction( ctx, OPCODE_END_OF_LIST, 0 );
   (void)n;

   /* Destroy old list, if any */
   gl_destroy_list(ctx, ctx->CurrentListNum);
   /* Install the list */
   HashInsert(ctx->Shared->DisplayList, ctx->CurrentListNum, ctx->CurrentListPtr);

   ctx->CurrentListNum = 0;
   ctx->CurrentListPtr = NULL;
   ctx->ExecuteFlag = GL_TRUE;
   ctx->CompileFlag = GL_FALSE;

   ctx->API = ctx->Exec;   /* Switch the API function pointers */
}