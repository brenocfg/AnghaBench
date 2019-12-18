#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int Alignment; scalar_t__ RowLength; int SkipRows; int SkipPixels; scalar_t__ SwapBytes; } ;
struct TYPE_12__ {double DepthBias; double DepthScale; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* ReadDepthSpanFloat ) (TYPE_5__*,int,int,int,int*) ;int /*<<< orphan*/  (* ReadDepthSpanInt ) (TYPE_5__*,int,int,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {TYPE_4__ Pack; TYPE_3__ Pixel; TYPE_2__ Driver; TYPE_1__* Visual; } ;
struct TYPE_10__ {scalar_t__ DepthBits; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  int GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLsizei ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  int GLint ;
typedef  int GLfloat ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLdepth ;
typedef  TYPE_5__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;
typedef  int GLboolean ;

/* Variables and functions */
 int CEILING (int,int) ; 
 int CLAMP (int,double,double) ; 
 int /*<<< orphan*/  FLOAT_TO_BYTE (int) ; 
 int /*<<< orphan*/  FLOAT_TO_INT (int) ; 
 int /*<<< orphan*/  FLOAT_TO_SHORT (int) ; 
 int /*<<< orphan*/  FLOAT_TO_UBYTE (int) ; 
 int /*<<< orphan*/  FLOAT_TO_UINT (int) ; 
 int /*<<< orphan*/  FLOAT_TO_USHORT (int) ; 
#define  GL_BYTE 134 
#define  GL_FLOAT 133 
#define  GL_INT 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 int MAX_DEPTH ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  gl_error (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int gl_sizeof_type (int) ; 
 int /*<<< orphan*/  gl_swap2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gl_swap4 (int*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int,int,int,int*) ; 

__attribute__((used)) static void read_depth_pixels( GLcontext *ctx,
                               GLint x, GLint y,
			       GLsizei width, GLsizei height,
			       GLenum type, GLvoid *pixels )
{
   GLint i, j;
   GLuint a, s, k, l, start;
   GLboolean bias_or_scale;

   /* Error checking */
   if (ctx->Visual->DepthBits<=0) {
      /* No depth buffer */
      gl_error( ctx, GL_INVALID_OPERATION, "glReadPixels" );
      return;
   }

   bias_or_scale = ctx->Pixel.DepthBias!=0.0 || ctx->Pixel.DepthScale!=1.0;

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

   if (type==GL_UNSIGNED_INT && !bias_or_scale && !ctx->Pack.SwapBytes) {
      /* Special case: directly read 32-bit unsigned depth values. */
      /* Compute shift value to scale depth values up to 32-bit uints. */
      GLuint shift = 0;
      GLuint max = MAX_DEPTH;
      while ((max&0x80000000)==0) {
         max = max << 1;
         shift++;
      }
      for (j=0;j<height;j++,y++) {
         GLuint *dst = (GLuint *) pixels + start + j * k;
         (*ctx->Driver.ReadDepthSpanInt)( ctx, width, x, y, (GLdepth*) dst);
         for (i=0;i<width;i++) {
            dst[i] = dst[i] << shift;
         }
      }
   }
   else {
      /* General case (slow) */
      for (j=0;j<height;j++,y++) {
         GLfloat depth[MAX_WIDTH];

         (*ctx->Driver.ReadDepthSpanFloat)( ctx, width, x, y, depth );

         if (bias_or_scale) {
            for (i=0;i<width;i++) {
               GLfloat d;
               d = depth[i] * ctx->Pixel.DepthScale + ctx->Pixel.DepthBias;
               depth[i] = CLAMP( d, 0.0, 1.0 );
            }
         }

         switch (type) {
            case GL_UNSIGNED_BYTE:
               {
                  GLubyte *dst = (GLubyte *) pixels + start + j * k;
                  for (i=0;i<width;i++) {
                     *dst++ = FLOAT_TO_UBYTE( depth[i] );
                  }
               }
               break;
            case GL_BYTE:
               {
                  GLbyte *dst = (GLbyte *) pixels + start + j * k;
                  for (i=0;i<width;i++) {
                     *dst++ = FLOAT_TO_BYTE( depth[i] );
                  }
               }
               break;
            case GL_UNSIGNED_SHORT:
               {
                  GLushort *dst = (GLushort *) pixels + start + j * k;
                  for (i=0;i<width;i++) {
                     *dst++ = FLOAT_TO_USHORT( depth[i] );
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
                     *dst++ = FLOAT_TO_SHORT( depth[i] );
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
                     *dst++ = FLOAT_TO_UINT( depth[i] );
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
                     *dst++ = FLOAT_TO_INT( depth[i] );
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
                     *dst++ = depth[i];
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
}