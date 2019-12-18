#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gl_image {void** Data; scalar_t__ RefCount; scalar_t__ Type; scalar_t__ Format; scalar_t__ Components; scalar_t__ Height; scalar_t__ Width; } ;
struct TYPE_6__ {int /*<<< orphan*/  SwapBytes; scalar_t__ LsbFirst; } ;
struct TYPE_5__ {TYPE_4__ Unpack; } ;
typedef  void* GLvoid ;
typedef  int GLushort ;
typedef  int GLuint ;
typedef  void* GLubyte ;
typedef  int GLshort ;
typedef  scalar_t__ GLint ;
typedef  void* GLfloat ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_1__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;
typedef  int GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_TO_FLOAT (int /*<<< orphan*/ ) ; 
 scalar_t__ CEILING (scalar_t__,int) ; 
 scalar_t__ GL_BITMAP ; 
#define  GL_BYTE 134 
 scalar_t__ GL_COLOR_INDEX ; 
 scalar_t__ GL_DEPTH_COMPONENT ; 
#define  GL_FLOAT 133 
#define  GL_INT 132 
#define  GL_SHORT 131 
 scalar_t__ GL_STENCIL_INDEX ; 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 void* INT_TO_FLOAT (scalar_t__) ; 
 int /*<<< orphan*/  MEMCPY (void**,void**,scalar_t__) ; 
 void* SHORT_TO_FLOAT (int) ; 
 int /*<<< orphan*/  UBYTE_TO_FLOAT (void*) ; 
 void* UINT_TO_FLOAT (int) ; 
 void* USHORT_TO_FLOAT (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void**) ; 
 scalar_t__ gl_components_in_format (scalar_t__) ; 
 int /*<<< orphan*/  gl_flip_bytes (void**,scalar_t__) ; 
 void** gl_pixel_addr_in_image (TYPE_4__*,void* const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gl_problem (TYPE_1__*,char*) ; 
 scalar_t__ malloc (int) ; 

struct gl_image *gl_unpack_image( GLcontext *ctx,
                                  GLint width, GLint height,
                                  GLenum srcFormat, GLenum srcType,
                                  const GLvoid *pixels )
{
   GLint components;
   GLenum destType;

   if (srcType==GL_UNSIGNED_BYTE) {
      destType = GL_UNSIGNED_BYTE;
   }
   else if (srcType==GL_BITMAP) {
      destType = GL_BITMAP;
   }
   else {
      destType = GL_FLOAT;
   }

   components = gl_components_in_format( srcFormat );

   if (components < 0)
      return NULL;

   if (srcType==GL_BITMAP || destType==GL_BITMAP) {
      struct gl_image *image;
      GLint bytes, i, width_in_bytes;
      GLubyte *buffer, *dst;
      assert( srcType==GL_BITMAP );
      assert( destType==GL_BITMAP );

      /* Alloc dest storage */
      if (width > 0 && height > 0)
         bytes = ((width+7)/8 * height);
      else
         bytes = 0;
      if (bytes>0 && pixels!=NULL) {
         buffer = (GLubyte *) malloc( bytes );
         if (!buffer) {
            return NULL;
         }
         /* Copy/unpack pixel data to buffer */
         width_in_bytes = CEILING( width, 8 );
         dst = buffer;
         for (i=0; i<height; i++) {
            GLvoid *src = gl_pixel_addr_in_image( &ctx->Unpack, pixels,
                                                  width, height,
                                                  GL_COLOR_INDEX, srcType,
                                                  i);
            if (!src) {
               free(buffer);
               return NULL;
            }
            MEMCPY( dst, src, width_in_bytes );
            dst += width_in_bytes;
         }
         /* Bit flipping */
         if (ctx->Unpack.LsbFirst) {
            gl_flip_bytes( buffer, bytes );
         }
      }
      else {
         /* a 'null' bitmap */
         buffer = NULL;
      }

      image = (struct gl_image *) malloc( sizeof(struct gl_image) );
      if (image) {
         image->Width = width;
         image->Height = height;
         image->Components = 0;
         image->Format = GL_COLOR_INDEX;
         image->Type = GL_BITMAP;
         image->Data = buffer;
         image->RefCount = 0;
      }
      else {
         if (buffer)
            free( buffer );
         return NULL;
      }
      return image;
   }
   else if (srcFormat==GL_DEPTH_COMPONENT) {
      /* TODO: pack as GLdepth values (GLushort or GLuint) */

   }
   else if (srcFormat==GL_STENCIL_INDEX) {
      /* TODO: pack as GLstencil (GLubyte or GLushort) */

   }
   else if (destType==GL_UNSIGNED_BYTE) {
      struct gl_image *image;
      GLint width_in_bytes;
      GLubyte *buffer, *dst;
      GLint i;
      assert( srcType==GL_UNSIGNED_BYTE );

      width_in_bytes = width * components * sizeof(GLubyte);
      buffer = (GLubyte *) malloc( height * width_in_bytes );
      if (!buffer) {
         return NULL;
      }
      /* Copy/unpack pixel data to buffer */
      dst = buffer;
      for (i=0;i<height;i++) {
         GLubyte *src = (GLubyte *) gl_pixel_addr_in_image( &ctx->Unpack,
                        pixels, width, height, srcFormat, srcType, i);
         if (!src) {
            free(buffer);
            return NULL;
         }
         MEMCPY( dst, src, width_in_bytes );
         dst += width_in_bytes;
      }

      if (ctx->Unpack.LsbFirst) {
         gl_flip_bytes( buffer, height * width_in_bytes );
      }

      image = (struct gl_image *) malloc( sizeof(struct gl_image) );
      if (image) {
         image->Width = width;
         image->Height = height;
         image->Components = components;
         image->Format = srcFormat;
         image->Type = GL_UNSIGNED_BYTE;
         image->Data = buffer;
         image->RefCount = 0;
      }
      else {
         free( buffer );
         return NULL;
      }
      return image;
   }
   else if (destType==GL_FLOAT) {
      struct gl_image *image;
      GLfloat *buffer, *dst;
      GLint elems_per_row;
      GLint i, j;
      GLboolean normalize;
      elems_per_row = width * components;
      buffer = (GLfloat *) malloc( height * elems_per_row * sizeof(GLfloat));
      if (!buffer) {
         return NULL;
      }

      normalize = (srcFormat != GL_COLOR_INDEX)
               && (srcFormat != GL_STENCIL_INDEX);

      dst = buffer;
      /**      img_pixels= pixels;*/
      for (i=0;i<height;i++) {
         GLvoid *src = gl_pixel_addr_in_image( &ctx->Unpack, pixels,
                                               width, height,
                                               srcFormat, srcType,
                                               i);
         if (!src) {
            free(buffer);
            return NULL;
         }

         switch (srcType) {
            case GL_UNSIGNED_BYTE:
               if (normalize) {
                  for (j=0;j<elems_per_row;j++) {
                     *dst++ = UBYTE_TO_FLOAT(((GLubyte*)src)[j]);
                  }
               }
               else {
                  for (j=0;j<elems_per_row;j++) {
                     *dst++ = (GLfloat) ((GLubyte*)src)[j];
                  }
               }
               break;
            case GL_BYTE:
               if (normalize) {
                  for (j=0;j<elems_per_row;j++) {
                     *dst++ = BYTE_TO_FLOAT(((GLbyte*)src)[j]);
                  }
               }
               else {
                  for (j=0;j<elems_per_row;j++) {
                     *dst++ = (GLfloat) ((GLbyte*)src)[j];
                  }
               }
               break;
            case GL_UNSIGNED_SHORT:
               if (ctx->Unpack.SwapBytes) {
                  for (j=0;j<elems_per_row;j++) {
                     GLushort value = ((GLushort*)src)[j];
                     value = ((value >> 8) & 0xff) | ((value&0xff) << 8);
                     if (normalize) {
                        *dst++ = USHORT_TO_FLOAT(value);
                     }
                     else {
                        *dst++ = (GLfloat) value;
                     }
                  }
               }
               else {
                  if (normalize) {
                     for (j=0;j<elems_per_row;j++) {
                        *dst++ = USHORT_TO_FLOAT(((GLushort*)src)[j]);
                     }
                  }
                  else {
                     for (j=0;j<elems_per_row;j++) {
                        *dst++ = (GLfloat) ((GLushort*)src)[j];
                     }
                  }
               }
               break;
            case GL_SHORT:
               if (ctx->Unpack.SwapBytes) {
                  for (j=0;j<elems_per_row;j++) {
                     GLshort value = ((GLshort*)src)[j];
                     value = ((value >> 8) & 0xff) | ((value&0xff) << 8);
                     if (normalize) {
                        *dst++ = SHORT_TO_FLOAT(value);
                     }
                     else {
                        *dst++ = (GLfloat) value;
                     }
                  }
               }
               else {
                  if (normalize) {
                     for (j=0;j<elems_per_row;j++) {
                        *dst++ = SHORT_TO_FLOAT(((GLshort*)src)[j]);
                     }
                  }
                  else {
                     for (j=0;j<elems_per_row;j++) {
                        *dst++ = (GLfloat) ((GLshort*)src)[j];
                     }
                  }
               }
               break;
            case GL_UNSIGNED_INT:
               if (ctx->Unpack.SwapBytes) {
                  GLuint value;
                  for (j=0;j<elems_per_row;j++) {
                     value = ((GLuint*)src)[j];
                     value = ((value & 0xff000000) >> 24)
                           | ((value & 0x00ff0000) >> 8)
                           | ((value & 0x0000ff00) << 8)
                           | ((value & 0x000000ff) << 24);
                     if (normalize) {
                        *dst++ = UINT_TO_FLOAT(value);
                     }
                     else {
                        *dst++ = (GLfloat) value;
                     }
                  }
               }
               else {
                  if (normalize) {
                     for (j=0;j<elems_per_row;j++) {
                        *dst++ = UINT_TO_FLOAT(((GLuint*)src)[j]);
                     }
                  }
                  else {
                     for (j=0;j<elems_per_row;j++) {
                        *dst++ = (GLfloat) ((GLuint*)src)[j];
                     }
                  }
               }
               break;
            case GL_INT:
               if (ctx->Unpack.SwapBytes) {
                  GLint value;
                  for (j=0;j<elems_per_row;j++) {
                     value = ((GLint*)src)[j];
                     value = ((value & 0xff000000) >> 24)
                           | ((value & 0x00ff0000) >> 8)
                           | ((value & 0x0000ff00) << 8)
                           | ((value & 0x000000ff) << 24);
                     if (normalize) {
                        *dst++ = INT_TO_FLOAT(value);
                     }
                     else {
                        *dst++ = (GLfloat) value;
                     }
                  }
               }
               else {
                  if (normalize) {
                     for (j=0;j<elems_per_row;j++) {
                        *dst++ = INT_TO_FLOAT(((GLint*)src)[j]);
                     }
                  }
                  else {
                     for (j=0;j<elems_per_row;j++) {
                        *dst++ = (GLfloat) ((GLint*)src)[j];
                     }
                  }
               }
               break;
            case GL_FLOAT:
               if (ctx->Unpack.SwapBytes) {
                  GLint value;
                  for (j=0;j<elems_per_row;j++) {
                     value = ((GLuint*)src)[j];
                     value = ((value & 0xff000000) >> 24)
                           | ((value & 0x00ff0000) >> 8)
                           | ((value & 0x0000ff00) << 8)
                           | ((value & 0x000000ff) << 24);
                     *dst++ = *((GLfloat*) &value);
                  }
               }
               else {
                  MEMCPY( dst, src, elems_per_row*sizeof(GLfloat) );
                  dst += elems_per_row;
               }
               break;
            default:
               gl_problem(ctx, "Bad type in gl_unpack_image3D");
               return NULL;
         } /*switch*/
      } /* for height */

      image = (struct gl_image *) malloc( sizeof(struct gl_image) );
      if (image) {
         image->Width = width;
         image->Height = height;
         image->Components = components;
         image->Format = srcFormat;
         image->Type = GL_FLOAT;
         image->Data = buffer;
         image->RefCount = 0;
      }
      else {
         free( buffer );
         return NULL;
      }
      return image;
   }
   else {
      gl_problem(ctx, "Bad dest type in gl_unpack_image3D");
      return NULL;
   }
   return NULL;  /* never get here */
}