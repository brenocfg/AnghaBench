#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t Alignment; scalar_t__ RowLength; size_t SkipRows; size_t SkipPixels; int /*<<< orphan*/  SwapBytes; } ;
struct TYPE_11__ {size_t IndexShift; scalar_t__ IndexOffset; size_t* MapItoI; scalar_t__ MapColorFlag; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* ReadIndexSpan ) (TYPE_5__*,scalar_t__,scalar_t__,scalar_t__,size_t*) ;} ;
struct TYPE_13__ {TYPE_4__ Pack; TYPE_3__ Pixel; TYPE_2__ Driver; TYPE_1__* Visual; } ;
struct TYPE_9__ {scalar_t__ RGBAflag; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  scalar_t__ GLsizei ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  TYPE_5__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;

/* Variables and functions */
 size_t CEILING (size_t,size_t) ; 
#define  GL_BYTE 134 
#define  GL_FLOAT 133 
#define  GL_INT 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  gl_error (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 size_t gl_sizeof_type (int) ; 
 int /*<<< orphan*/  gl_swap2 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gl_swap4 (size_t*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,scalar_t__,scalar_t__,scalar_t__,size_t*) ; 

__attribute__((used)) static void read_index_pixels( GLcontext *ctx,
                               GLint x, GLint y,
			       GLsizei width, GLsizei height,
			       GLenum type, GLvoid *pixels )
{
   GLint i, j;
   GLuint a, s, k, l, start;

   /* error checking */
   if (ctx->Visual->RGBAflag) {
      gl_error( ctx, GL_INVALID_OPERATION, "glReadPixels" );
      return;
   }

   /* Size of each component */
   s = gl_sizeof_type( type );
   if (s<=0) {
      gl_error( ctx, GL_INVALID_ENUM, "glReadPixels(type)" );
      return;
   }

   /* Compute packing parameters */
   a = ctx->Pack.Alignment;
   if (ctx->Pack.RowLength>0) {
      l = ctx->Pack.RowLength;
   }
   else {
      l = width;
   }
   /* k = offset between rows in components */
   if (s>=a) {
      k = l;
   }
   else {
      k = a/s * CEILING( s*l, a );
   }

   /* offset to first component returned */
   start = ctx->Pack.SkipRows * k + ctx->Pack.SkipPixels;

   /* process image row by row */
   for (j=0;j<height;j++,y++) {
      GLuint index[MAX_WIDTH];
      (*ctx->Driver.ReadIndexSpan)( ctx, width, x, y, index );

      if (ctx->Pixel.IndexShift!=0 || ctx->Pixel.IndexOffset!=0) {
	 GLuint s;
	 if (ctx->Pixel.IndexShift<0) {
	    /* right shift */
	    s = -ctx->Pixel.IndexShift;
	    for (i=0;i<width;i++) {
	       index[i] = (index[i] >> s) + ctx->Pixel.IndexOffset;
	    }
	 }
	 else {
	    /* left shift */
	    s = ctx->Pixel.IndexShift;
	    for (i=0;i<width;i++) {
	       index[i] = (index[i] << s) + ctx->Pixel.IndexOffset;
	    }
	 }
      }

      if (ctx->Pixel.MapColorFlag) {
	 for (i=0;i<width;i++) {
	    index[i] = ctx->Pixel.MapItoI[ index[i] ];
	 }
      }

      switch (type) {
	 case GL_UNSIGNED_BYTE:
	    {
	       GLubyte *dst = (GLubyte *) pixels + start + j * k;
	       for (i=0;i<width;i++) {
		  *dst++ = (GLubyte) index[i];
	       }
	    }
	    break;
	 case GL_BYTE:
	    {
	       GLbyte *dst = (GLbyte *) pixels + start + j * k;
	       for (i=0;i<width;i++) {
		  *dst++ = (GLbyte) index[i];
	       }
	    }
	    break;
	 case GL_UNSIGNED_SHORT:
	    {
	       GLushort *dst = (GLushort *) pixels + start + j * k;
	       for (i=0;i<width;i++) {
		  *dst++ = (GLushort) index[i];
	       }
	       if (ctx->Pack.SwapBytes) {
		  gl_swap2( (GLushort *) pixels + start + j * k, width );
	       }
	    }
	    break;
	 case GL_SHORT:
	    {
	       GLshort *dst = (GLshort *) pixels + start + j * k;
	       for (i=0;i<width;i++) {
		  *dst++ = (GLshort) index[i];
	       }
	       if (ctx->Pack.SwapBytes) {
		  gl_swap2( (GLushort *) pixels + start + j * k, width );
	       }
	    }
	    break;
	 case GL_UNSIGNED_INT:
	    {
	       GLuint *dst = (GLuint *) pixels + start + j * k;
	       for (i=0;i<width;i++) {
		  *dst++ = (GLuint) index[i];
	       }
	       if (ctx->Pack.SwapBytes) {
		  gl_swap4( (GLuint *) pixels + start + j * k, width );
	       }
	    }
	    break;
	 case GL_INT:
	    {
	       GLint *dst = (GLint *) pixels + start + j * k;
	       for (i=0;i<width;i++) {
		  *dst++ = (GLint) index[i];
	       }
	       if (ctx->Pack.SwapBytes) {
		  gl_swap4( (GLuint *) pixels + start + j * k, width );
	       }
	    }
	    break;
	 case GL_FLOAT:
	    {
	       GLfloat *dst = (GLfloat *) pixels + start + j * k;
	       for (i=0;i<width;i++) {
		  *dst++ = (GLfloat) index[i];
	       }
	       if (ctx->Pack.SwapBytes) {
		  gl_swap4( (GLuint *) pixels + start + j * k, width );
	       }
	    }
	    break;
         default:
            gl_error( ctx, GL_INVALID_ENUM, "glReadPixels(type)" );
      }
   }
}