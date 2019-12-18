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
struct TYPE_5__ {int IndexType; void* IndexPtr; scalar_t__ IndexStride; scalar_t__ IndexStrideB; } ;
struct TYPE_6__ {TYPE_1__ Array; } ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  scalar_t__ GLsizei ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLdouble ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLbyte ;

/* Variables and functions */
#define  GL_DOUBLE 131 
#define  GL_FLOAT 130 
#define  GL_INT 129 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_SHORT 128 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_IndexPointer( GLcontext *ctx,
                      GLenum type, GLsizei stride, const GLvoid *ptr )
{
   if (stride<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glIndexPointer(stride)" );
      return;
   }
   switch (type) {
      case GL_SHORT:
         ctx->Array.IndexStrideB = stride ? stride : sizeof(GLbyte);
         break;
      case GL_INT:
         ctx->Array.IndexStrideB = stride ? stride : sizeof(GLint);
         break;
      case GL_FLOAT:
         ctx->Array.IndexStrideB = stride ? stride : sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         ctx->Array.IndexStrideB = stride ? stride : sizeof(GLdouble);
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glIndexPointer(type)" );
         return;
   }
   ctx->Array.IndexType = type;
   ctx->Array.IndexStride = stride;
   ctx->Array.IndexPtr = (void *) ptr;
}