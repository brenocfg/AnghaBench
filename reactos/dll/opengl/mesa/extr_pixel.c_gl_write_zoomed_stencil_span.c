#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ZoomX; int ZoomY; } ;
struct TYPE_8__ {TYPE_2__ Pixel; TYPE_1__* Buffer; } ;
struct TYPE_6__ {int Height; int /*<<< orphan*/  Width; } ;
typedef  int GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLint ;
typedef  int GLfloat ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 scalar_t__ ABSF (int) ; 
 int MAX_WIDTH ; 
 int MIN2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gl_write_stencil_span (TYPE_3__*,int,int,int,int /*<<< orphan*/ *) ; 

void
gl_write_zoomed_stencil_span( GLcontext *ctx,
                              GLuint n, GLint x, GLint y,
                              const GLubyte stencil[], GLint y0 )
{
   GLint m;
   GLint r0, r1, row, r;
   GLint i, j, skipcol;
   GLubyte zstencil[MAX_WIDTH];  /* zoomed stencil values */
   GLint maxwidth = MIN2( ctx->Buffer->Width, MAX_WIDTH );

   /* compute width of output row */
   m = (GLint) ABSF( n * ctx->Pixel.ZoomX );
   if (m==0) {
      return;
   }
   if (ctx->Pixel.ZoomX<0.0) {
      /* adjust x coordinate for left/right mirroring */
      x = x - m;
   }

   /* compute which rows to draw */
   row = y-y0;
   r0 = y0 + (GLint) (row * ctx->Pixel.ZoomY);
   r1 = y0 + (GLint) ((row+1) * ctx->Pixel.ZoomY);
   if (r0==r1) {
      return;
   }
   else if (r1<r0) {
      GLint rtmp = r1;
      r1 = r0;
      r0 = rtmp;
   }

   /* return early if r0...r1 is above or below window */
   if (r0<0 && r1<0) {
      /* below window */
      return;
   }
   if (r0>=ctx->Buffer->Height && r1>=ctx->Buffer->Height) {
      /* above window */
      return;
   }

   /* check if left edge is outside window */
   skipcol = 0;
   if (x<0) {
      skipcol = -x;
      m += x;
   }
   /* make sure span isn't too long or short */
   if (m>maxwidth) {
      m = maxwidth;
   }
   else if (m<=0) {
      return;
   }

   assert( m <= MAX_WIDTH );

   /* zoom the span horizontally */
   if (ctx->Pixel.ZoomX==-1.0F) {
      /* n==m */
      for (j=0;j<m;j++) {
         i = n - (j+skipcol) - 1;
         zstencil[j] = stencil[i];
      }
   }
   else {
      GLfloat xscale = 1.0F / ctx->Pixel.ZoomX;
      for (j=0;j<m;j++) {
         i = (j+skipcol) * xscale;
         if (i<0)  i = n + i - 1;
         zstencil[j] = stencil[i];
      }
   }

   /* write the span */
   for (r=r0; r<r1; r++) {
      gl_write_stencil_span( ctx, m, x+skipcol, r, zstencil );
   }
}