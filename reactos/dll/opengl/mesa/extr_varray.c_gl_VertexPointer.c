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
struct TYPE_5__ {int VertexSize; int VertexType; void* VertexPtr; scalar_t__ VertexStride; scalar_t__ VertexStrideB; } ;
struct TYPE_6__ {TYPE_1__ Array; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  scalar_t__ GLsizei ;
typedef  int /*<<< orphan*/  GLshort ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLdouble ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_DOUBLE 131 
#define  GL_FLOAT 130 
#define  GL_INT 129 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_SHORT 128 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_VertexPointer( GLcontext *ctx,
                       GLint size, GLenum type, GLsizei stride,
                       const GLvoid *ptr )
{
   if (size<2 || size>4) {
      gl_error( ctx, GL_INVALID_VALUE, "glVertexPointer(size)" );
      return;
   }
   if (stride<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glVertexPointer(stride)" );
      return;
   }
   switch (type) {
      case GL_SHORT:
         ctx->Array.VertexStrideB = stride ? stride : size*sizeof(GLshort);
         break;
      case GL_INT:
         ctx->Array.VertexStrideB = stride ? stride : size*sizeof(GLint);
         break;
      case GL_FLOAT:
         ctx->Array.VertexStrideB = stride ? stride : size*sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         ctx->Array.VertexStrideB = stride ? stride : size*sizeof(GLdouble);
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glVertexPointer(type)" );
         return;
   }
   ctx->Array.VertexSize = size;
   ctx->Array.VertexType = type;
   ctx->Array.VertexStride = stride;
   ctx->Array.VertexPtr = (void *) ptr;
}