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
struct TYPE_12__ {int ColorMask; int IndexMask; void* SWmasking; } ;
struct TYPE_11__ {scalar_t__ (* IndexMask ) (TYPE_4__*,int) ;scalar_t__ (* ColorMask ) (TYPE_4__*,void*,void*,void*,void*) ;} ;
struct TYPE_13__ {TYPE_3__ Color; TYPE_2__ Driver; TYPE_1__* Visual; } ;
struct TYPE_10__ {scalar_t__ RGBAflag; } ;
typedef  TYPE_4__ GLcontext ;
typedef  void* GLboolean ;

/* Variables and functions */
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 scalar_t__ stub1 (TYPE_4__*,void*,void*,void*,void*) ; 
 scalar_t__ stub2 (TYPE_4__*,void*,void*,void*,void*) ; 
 scalar_t__ stub3 (TYPE_4__*,int) ; 
 scalar_t__ stub4 (TYPE_4__*,int) ; 

__attribute__((used)) static void update_pixel_masking( GLcontext *ctx )
{
   if (ctx->Visual->RGBAflag) {
      if (ctx->Color.ColorMask==0xf) {
         /* disable masking */
         if (ctx->Driver.ColorMask) {
            (void) (*ctx->Driver.ColorMask)( ctx, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
         }
         ctx->Color.SWmasking = GL_FALSE;
      }
      else {
         /* Ask driver to do color masking, if it can't then
          * do it in software
          */
         GLboolean red   = (ctx->Color.ColorMask & 8) ? GL_TRUE : GL_FALSE;
         GLboolean green = (ctx->Color.ColorMask & 4) ? GL_TRUE : GL_FALSE;
         GLboolean blue  = (ctx->Color.ColorMask & 2) ? GL_TRUE : GL_FALSE;
         GLboolean alpha = (ctx->Color.ColorMask & 1) ? GL_TRUE : GL_FALSE;
         if (ctx->Driver.ColorMask
             && (*ctx->Driver.ColorMask)( ctx, red, green, blue, alpha )) {
            ctx->Color.SWmasking = GL_FALSE;
         }
         else {
            ctx->Color.SWmasking = GL_TRUE;
         }
      }
   }
   else {
      if (ctx->Color.IndexMask==0xffffffff) {
         /* disable masking */
         if (ctx->Driver.IndexMask) {
            (void) (*ctx->Driver.IndexMask)( ctx, 0xffffffff );
         }
         ctx->Color.SWmasking = GL_FALSE;
      }
      else {
         /* Ask driver to do index masking, if it can't then
          * do it in software
          */
         if (ctx->Driver.IndexMask
             && (*ctx->Driver.IndexMask)( ctx, ctx->Color.IndexMask )) {
            ctx->Color.SWmasking = GL_FALSE;
         }
         else {
            ctx->Color.SWmasking = GL_TRUE;
         }
      }
   }
}