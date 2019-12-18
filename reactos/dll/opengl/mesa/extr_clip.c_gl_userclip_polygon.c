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
struct vertex_buffer {float** Eye; size_t Free; int /*<<< orphan*/ * Edgeflag; } ;
struct TYPE_5__ {float** ClipEquation; scalar_t__* ClipEnabled; } ;
struct TYPE_6__ {scalar_t__ ClipMask; TYPE_1__ Transform; struct vertex_buffer* VB; } ;
typedef  size_t GLuint ;
typedef  float GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  EYE_SPACE ; 
 scalar_t__ INSIDE (size_t,float,float,float,float) ; 
 size_t MAX_CLIP_PLANES ; 
 int /*<<< orphan*/  MEMCPY (size_t*,size_t*,size_t) ; 
 int VB_SIZE ; 
 int /*<<< orphan*/  interpolate_aux (TYPE_2__*,int /*<<< orphan*/ ,size_t,float,size_t,size_t) ; 

GLuint gl_userclip_polygon( GLcontext* ctx, GLuint n, GLuint vlist[] )
{
   struct vertex_buffer* VB = ctx->VB;

   GLuint vlist2[VB_SIZE];
   GLuint *inlist, *outlist;
   GLuint incount, outcount;
   GLuint curri, currj;
   GLuint previ, prevj;
   GLuint p;

   /* initialize input vertex list */
   incount = n;
   inlist = vlist;
   outlist = vlist2;

   for (p=0;p<MAX_CLIP_PLANES;p++) {
      if (ctx->Transform.ClipEnabled[p]) {
	 register float a = ctx->Transform.ClipEquation[p][0];
	 register float b = ctx->Transform.ClipEquation[p][1];
	 register float c = ctx->Transform.ClipEquation[p][2];
	 register float d = ctx->Transform.ClipEquation[p][3];

	 if (incount<3)  return 0;

	 /* initialize prev to be last in the input list */
	 previ = incount - 1;
	 prevj = inlist[previ];

         outcount = 0;

         for (curri=0;curri<incount;curri++) {
	    currj = inlist[curri];

            if (INSIDE(currj, a,b,c,d)) {
               if (INSIDE(prevj, a,b,c,d)) {
                  /* both verts are inside ==> copy current to outlist */
		  outlist[outcount++] = currj;
               }
               else {
                  /* current is inside and previous is outside ==> clip */
                  GLfloat dx, dy, dz, dw, t, denom;
		  /* compute t */
		  dx = VB->Eye[prevj][0] - VB->Eye[currj][0];
		  dy = VB->Eye[prevj][1] - VB->Eye[currj][1];
		  dz = VB->Eye[prevj][2] - VB->Eye[currj][2];
		  dw = VB->Eye[prevj][3] - VB->Eye[currj][3];
		  denom = dx*a + dy*b + dz*c + dw*d;
		  if (denom==0.0) {
		     t = 0.0;
		  }
		  else {
		     t = -(VB->Eye[currj][0]*a+VB->Eye[currj][1]*b
		       +VB->Eye[currj][2]*c+VB->Eye[currj][3]*d) / denom;
                     if (t>1.0F) {
                        t = 1.0F;
                     }
		  }
		  /* interpolate new vertex position */
		  VB->Eye[VB->Free][0] = VB->Eye[currj][0] + t*dx;
		  VB->Eye[VB->Free][1] = VB->Eye[currj][1] + t*dy;
		  VB->Eye[VB->Free][2] = VB->Eye[currj][2] + t*dz;
		  VB->Eye[VB->Free][3] = VB->Eye[currj][3] + t*dw;

		  /* interpolate color, index, and/or texture coord */
		  if (ctx->ClipMask) {
		     interpolate_aux( ctx, EYE_SPACE, VB->Free, t, currj, prevj);
		  }
		  VB->Edgeflag[VB->Free] = VB->Edgeflag[prevj];

		  /* output new vertex */
		  outlist[outcount++] = VB->Free;
		  VB->Free++;
		  if (VB->Free==VB_SIZE)   VB->Free = 1;
		  /* output current vertex */
		  outlist[outcount++] = currj;
               }
            }
            else {
               if (INSIDE(prevj, a,b,c,d)) {
                  /* current is outside and previous is inside ==> clip */
                  GLfloat dx, dy, dz, dw, t, denom;
		  /* compute t */
                  dx = VB->Eye[currj][0]-VB->Eye[prevj][0];
                  dy = VB->Eye[currj][1]-VB->Eye[prevj][1];
                  dz = VB->Eye[currj][2]-VB->Eye[prevj][2];
                  dw = VB->Eye[currj][3]-VB->Eye[prevj][3];
		  denom = dx*a + dy*b + dz*c + dw*d;
		  if (denom==0.0) {
		     t = 0.0;
		  }
		  else {
		     t = -(VB->Eye[prevj][0]*a+VB->Eye[prevj][1]*b
		       +VB->Eye[prevj][2]*c+VB->Eye[prevj][3]*d) / denom;
                     if (t>1.0F) {
                        t = 1.0F;
                     }
		  }
		  /* interpolate new vertex position */
		  VB->Eye[VB->Free][0] = VB->Eye[prevj][0] + t*dx;
		  VB->Eye[VB->Free][1] = VB->Eye[prevj][1] + t*dy;
		  VB->Eye[VB->Free][2] = VB->Eye[prevj][2] + t*dz;
		  VB->Eye[VB->Free][3] = VB->Eye[prevj][3] + t*dw;

		  /* interpolate color, index, and/or texture coord */
		  if (ctx->ClipMask) {
		     interpolate_aux( ctx, EYE_SPACE, VB->Free, t, prevj, currj);
		  }
		  VB->Edgeflag[VB->Free] = VB->Edgeflag[prevj];

		  /* output new vertex */
		  outlist[outcount++] = VB->Free;
		  VB->Free++;
		  if (VB->Free==VB_SIZE)   VB->Free = 1;
	       }
               /* else  both verts are outside ==> do nothing */
            }

	    previ = curri;
	    prevj = currj;

	    /* check for overflowing vertex buffer */
            if (outcount>=VB_SIZE-1) {
               /* Too many vertices */
               if (outlist!=vlist2) {
                  MEMCPY( vlist, vlist2, outcount * sizeof(GLuint) );
               }
               return VB_SIZE-1;
            }

         }  /* for i */

         /* swap inlist and outlist pointers */
         {
            GLuint *tmp;
            tmp = inlist;
            inlist = outlist;
            outlist = tmp;
            incount = outcount;
         }

      } /* if */
   } /* for p */

   /* outlist points to the list of vertices resulting from the last */
   /* clipping.  If outlist == vlist2 then we have to copy the vertices */
   /* back to vlist */
   if (outlist!=vlist2) {
      MEMCPY( vlist, vlist2, outcount * sizeof(GLuint) );
   }

   return outcount;
}