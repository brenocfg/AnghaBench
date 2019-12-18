#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vertex_buffer {size_t* Findex; size_t* Bindex; void*** TexCoord; void*** Eye; void*** Bcolor; void*** Fcolor; } ;
struct TYPE_3__ {int ClipMask; struct vertex_buffer* VB; } ;
typedef  size_t GLuint ;
typedef  scalar_t__ GLint ;
typedef  void* GLfloat ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int CLIP_BCOLOR_BIT ; 
 int CLIP_BINDEX_BIT ; 
 int CLIP_FCOLOR_BIT ; 
 int CLIP_FINDEX_BIT ; 
 size_t CLIP_SPACE ; 
 int CLIP_TEXTURE_BIT ; 
 void* LINTERP (void*,void*,void*) ; 

void interpolate_aux( GLcontext* ctx, GLuint space,
                      GLuint dst, GLfloat t, GLuint in, GLuint out )
{
   struct vertex_buffer* VB = ctx->VB;

   if (ctx->ClipMask & CLIP_FCOLOR_BIT) {
      VB->Fcolor[dst][0] = LINTERP( t, VB->Fcolor[in][0], VB->Fcolor[out][0] );
      VB->Fcolor[dst][1] = LINTERP( t, VB->Fcolor[in][1], VB->Fcolor[out][1] );
      VB->Fcolor[dst][2] = LINTERP( t, VB->Fcolor[in][2], VB->Fcolor[out][2] );
      VB->Fcolor[dst][3] = LINTERP( t, VB->Fcolor[in][3], VB->Fcolor[out][3] );
   }
   else if (ctx->ClipMask & CLIP_FINDEX_BIT) {
      VB->Findex[dst] = (GLuint) (GLint) LINTERP( t, (GLfloat) VB->Findex[in],
                                                 (GLfloat) VB->Findex[out] );
   }

   if (ctx->ClipMask & CLIP_BCOLOR_BIT) {
      VB->Bcolor[dst][0] = LINTERP( t, VB->Bcolor[in][0], VB->Bcolor[out][0] );
      VB->Bcolor[dst][1] = LINTERP( t, VB->Bcolor[in][1], VB->Bcolor[out][1] );
      VB->Bcolor[dst][2] = LINTERP( t, VB->Bcolor[in][2], VB->Bcolor[out][2] );
      VB->Bcolor[dst][3] = LINTERP( t, VB->Bcolor[in][3], VB->Bcolor[out][3] );
   }
   else if (ctx->ClipMask & CLIP_BINDEX_BIT) {
      VB->Bindex[dst] = (GLuint) (GLint) LINTERP( t, (GLfloat) VB->Bindex[in],
                                                 (GLfloat) VB->Bindex[out] );
   }

   if (ctx->ClipMask & CLIP_TEXTURE_BIT) {
      /* TODO: is more sophisticated texture coord interpolation needed?? */
      if (space==CLIP_SPACE) {
	 /* also interpolate eye Z component */
	 VB->Eye[dst][2] = LINTERP( t, VB->Eye[in][2], VB->Eye[out][2] );
      }
      VB->TexCoord[dst][0] = LINTERP(t,VB->TexCoord[in][0],VB->TexCoord[out][0]);
      VB->TexCoord[dst][1] = LINTERP(t,VB->TexCoord[in][1],VB->TexCoord[out][1]);
      VB->TexCoord[dst][2] = LINTERP(t,VB->TexCoord[in][2],VB->TexCoord[out][2]);
      VB->TexCoord[dst][3] = LINTERP(t,VB->TexCoord[in][3],VB->TexCoord[out][3]);
   }

}