#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {double ZoomX; double ZoomY; size_t IndexOffset; size_t IndexShift; size_t* MapStoS; scalar_t__ MapStencilFlag; } ;
struct TYPE_8__ {scalar_t__* RasterPos; } ;
struct TYPE_10__ {TYPE_2__ Pixel; TYPE_1__ Current; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  scalar_t__ GLuint ;
typedef  size_t GLubyte ;
typedef  scalar_t__ GLsizei ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;
typedef  size_t GLbyte ;
typedef  int GLboolean ;

/* Variables and functions */
#define  GL_BITMAP 135 
#define  GL_BYTE 134 
#define  GL_FLOAT 133 
#define  GL_INT 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  MEMCPY (size_t*,size_t*,scalar_t__) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_write_stencil_span (TYPE_3__*,scalar_t__,int,int,size_t*) ; 
 int /*<<< orphan*/  gl_write_zoomed_stencil_span (TYPE_3__*,scalar_t__,int,int,size_t*,int) ; 

__attribute__((used)) static void draw_stencil_pixels( GLcontext* ctx, GLsizei width, GLsizei height,
			         GLenum type, const GLvoid *pixels )
{
   GLint x, y, desty;
   GLuint i, j;
   GLboolean zoom;

   zoom = ctx->Pixel.ZoomX!=1.0 || ctx->Pixel.ZoomY!=1.0;

   /* Position, depth of pixels */
   x = (GLint) (ctx->Current.RasterPos[0] + 0.5F);
   y = (GLint) (ctx->Current.RasterPos[1] + 0.5F);
   desty = y;

   /* process the image row by row */
   for (i=0;i<height;i++,y++) {
      GLubyte stencil[MAX_WIDTH];

      /* convert to ubytes */
      switch (type) {
	 case GL_UNSIGNED_BYTE:
	    {
	       GLubyte *src = (GLubyte *) pixels + i * width;
	       MEMCPY( stencil, src, width );
	    }
	    break;
	 case GL_BYTE:
	    {
	       GLbyte *src = (GLbyte *) pixels + i * width;
	       MEMCPY( stencil, src, width );
	    }
	    break;
	 case GL_UNSIGNED_SHORT:
	    {
	       GLushort *src = (GLushort *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  stencil[j] = (GLubyte) ((*src++) & 0xff);
	       }
	    }
	    break;
	 case GL_SHORT:
	    {
	       GLshort *src = (GLshort *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  stencil[j] = (GLubyte) ((*src++) & 0xff);
	       }
	    }
	    break;
	 case GL_UNSIGNED_INT:
	    {
	       GLuint *src = (GLuint *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  stencil[j] = (GLubyte) ((*src++) & 0xff);
	       }
	    }
	    break;
	 case GL_INT:
	    {
	       GLint *src = (GLint *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  stencil[j] = (GLubyte) ((*src++) & 0xff);
	       }
	    }
	    break;
	 case GL_BITMAP:
	    /* TODO */
	    break;
	 case GL_FLOAT:
	    {
	       GLfloat *src = (GLfloat *) pixels + i * width;
	       for (j=0;j<width;j++) {
		  stencil[j] = (GLubyte) (((GLint) *src++) & 0xff);
	       }
	    }
	    break;
	 default:
	    gl_error( ctx, GL_INVALID_ENUM, "Internal: draw_stencil_pixels" );
      }

      /* apply shift and offset */
      if (ctx->Pixel.IndexOffset || ctx->Pixel.IndexShift) {
	 if (ctx->Pixel.IndexShift>=0) {
	    for (j=0;j<width;j++) {
	       stencil[j] = (stencil[j] << ctx->Pixel.IndexShift)
		          + ctx->Pixel.IndexOffset;
	    }
	 }
	 else {
	    for (j=0;j<width;j++) {
	       stencil[j] = (stencil[j] >> -ctx->Pixel.IndexShift)
		          + ctx->Pixel.IndexOffset;
	    }
	 }
      }

      /* mapping */
      if (ctx->Pixel.MapStencilFlag) {
	 for (j=0;j<width;j++) {
	    stencil[j] = ctx->Pixel.MapStoS[ stencil[j] ];
	 }
      }

      /* write stencil values to stencil buffer */
      if (zoom) {
         gl_write_zoomed_stencil_span( ctx, (GLuint) width, x, y, stencil, desty );
      }
      else {
         gl_write_stencil_span( ctx, (GLuint) width, x, y, stencil );
      }
   }
}