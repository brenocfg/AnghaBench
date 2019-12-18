#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* QuadFunc; } ;
struct TYPE_5__ {scalar_t__ RenderMode; TYPE_1__ Driver; scalar_t__ NoRaster; } ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_RENDER ; 
 void* null_quad ; 
 void* quad ; 

void gl_set_quad_function( GLcontext *ctx )
{
   if (ctx->RenderMode==GL_RENDER) {
      if (ctx->NoRaster) {
         ctx->Driver.QuadFunc = null_quad;
      }
      else if (ctx->Driver.QuadFunc) {
         /* Device driver will draw quads. */
      }
      else {
         ctx->Driver.QuadFunc = quad;
      }
   }
   else {
      /* if in feedback or selection mode we can fall back to triangle code */
      ctx->Driver.QuadFunc = quad;
   }      
}