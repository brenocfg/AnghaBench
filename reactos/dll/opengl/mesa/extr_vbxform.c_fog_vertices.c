#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vertex_buffer {scalar_t__ Start; scalar_t__ Bindex; scalar_t__ Eye; scalar_t__ Count; scalar_t__ Findex; scalar_t__ Bcolor; scalar_t__ Fcolor; } ;
struct TYPE_7__ {scalar_t__ LightTwoSide; TYPE_1__* Visual; struct vertex_buffer* VB; } ;
struct TYPE_6__ {scalar_t__ RGBAflag; } ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  gl_fog_color_vertices (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gl_fog_index_vertices (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void fog_vertices( GLcontext *ctx )
{
   struct vertex_buffer *VB = ctx->VB;

   if (ctx->Visual->RGBAflag) {
      /* Fog RGB colors */
      gl_fog_color_vertices( ctx, VB->Count - VB->Start,
                             VB->Eye + VB->Start,
                             VB->Fcolor + VB->Start );
      if (ctx->LightTwoSide) {
         gl_fog_color_vertices( ctx, VB->Count - VB->Start,
                                VB->Eye + VB->Start,
                                VB->Bcolor + VB->Start );
      }
   }
   else {
      /* Fog color indexes */
      gl_fog_index_vertices( ctx, VB->Count - VB->Start,
                             VB->Eye + VB->Start,
                             VB->Findex + VB->Start );
      if (ctx->LightTwoSide) {
         gl_fog_index_vertices( ctx, VB->Count - VB->Start,
                                VB->Eye + VB->Start,
                                VB->Bindex + VB->Start );
      }
   }
}