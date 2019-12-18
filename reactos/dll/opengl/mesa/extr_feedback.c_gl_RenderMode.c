#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int Count; int BufferSize; } ;
struct TYPE_9__ {int Hits; int /*<<< orphan*/  BufferSize; int /*<<< orphan*/  NameStackDepth; int /*<<< orphan*/  BufferCount; int /*<<< orphan*/  HitFlag; } ;
struct TYPE_11__ {int RenderMode; int /*<<< orphan*/  NewState; TYPE_2__ Feedback; TYPE_1__ Select; } ;
typedef  int GLint ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
#define  GL_FEEDBACK 130 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_RENDER 129 
#define  GL_SELECT 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_3__*) ; 
 int /*<<< orphan*/  NEW_ALL ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_warning (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  write_hit_record (TYPE_3__*) ; 

GLint gl_RenderMode( GLcontext *ctx, GLenum mode )
{
   GLint result;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glRenderMode" );
   }

   switch (ctx->RenderMode) {
      case GL_RENDER:
	 result = 0;
	 break;
      case GL_SELECT:
	 if (ctx->Select.HitFlag) {
	    write_hit_record( ctx );
	 }
	 if (ctx->Select.BufferCount > ctx->Select.BufferSize) {
	    /* overflow */
#ifdef DEBUG
            gl_warning(ctx, "Feedback buffer overflow");
#endif
	    result = -1;
	 }
	 else {
	    result = ctx->Select.Hits;
	 }
	 ctx->Select.BufferCount = 0;
	 ctx->Select.Hits = 0;
	 ctx->Select.NameStackDepth = 0;
	 break;
      case GL_FEEDBACK:
	 if (ctx->Feedback.Count > ctx->Feedback.BufferSize) {
	    /* overflow */
	    result = -1;
	 }
	 else {
	    result = ctx->Feedback.Count;
	 }
	 ctx->Feedback.Count = 0;
	 break;
      default:
	 gl_error( ctx, GL_INVALID_ENUM, "glRenderMode" );
	 return 0;
   }

   switch (mode) {
      case GL_RENDER:
         break;
      case GL_SELECT:
	 if (ctx->Select.BufferSize==0) {
	    /* haven't called glSelectBuffer yet */
	    gl_error( ctx, GL_INVALID_OPERATION, "glRenderMode" );
	 }
	 break;
      case GL_FEEDBACK:
	 if (ctx->Feedback.BufferSize==0) {
	    /* haven't called glFeedbackBuffer yet */
	    gl_error( ctx, GL_INVALID_OPERATION, "glRenderMode" );
	 }
	 break;
      default:
	 gl_error( ctx, GL_INVALID_ENUM, "glRenderMode" );
	 return 0;
   }

   ctx->RenderMode = mode;
   ctx->NewState |= NEW_ALL;

   return result;
}