#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* SWLogicOpEnabled; int /*<<< orphan*/  LogicOp; scalar_t__ IndexLogicOpEnabled; scalar_t__ ColorLogicOpEnabled; } ;
struct TYPE_11__ {scalar_t__ (* LogicOp ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {TYPE_3__ Color; TYPE_2__ Driver; TYPE_1__* Visual; } ;
struct TYPE_10__ {scalar_t__ RGBAflag; } ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COPY ; 
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_pixel_logic( GLcontext *ctx )
{
   if (ctx->Visual->RGBAflag) {
      /* RGBA mode blending w/ Logic Op */
      if (ctx->Color.ColorLogicOpEnabled) {
	 if (ctx->Driver.LogicOp
             && (*ctx->Driver.LogicOp)( ctx, ctx->Color.LogicOp )) {
	    /* Device driver can do logic, don't have to do it in software */
	    ctx->Color.SWLogicOpEnabled = GL_FALSE;
	 }
	 else {
	    /* Device driver can't do logic op so we do it in software */
	    ctx->Color.SWLogicOpEnabled = GL_TRUE;
	 }
      }
      else {
	 /* no logic op */
	 if (ctx->Driver.LogicOp) {
            (void) (*ctx->Driver.LogicOp)( ctx, GL_COPY );
         }
	 ctx->Color.SWLogicOpEnabled = GL_FALSE;
      }
   }
   else {
      /* CI mode Logic Op */
      if (ctx->Color.IndexLogicOpEnabled) {
	 if (ctx->Driver.LogicOp
             && (*ctx->Driver.LogicOp)( ctx, ctx->Color.LogicOp )) {
	    /* Device driver can do logic, don't have to do it in software */
	    ctx->Color.SWLogicOpEnabled = GL_FALSE;
	 }
	 else {
	    /* Device driver can't do logic op so we do it in software */
	    ctx->Color.SWLogicOpEnabled = GL_TRUE;
	 }
      }
      else {
	 /* no logic op */
	 if (ctx->Driver.LogicOp) {
            (void) (*ctx->Driver.LogicOp)( ctx, GL_COPY );
         }
	 ctx->Color.SWLogicOpEnabled = GL_FALSE;
      }
   }
}