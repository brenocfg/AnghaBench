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
struct gl_texture_image {scalar_t__ Border; scalar_t__ Width; scalar_t__ Data; } ;
struct TYPE_9__ {TYPE_1__* Current1D; } ;
struct TYPE_10__ {TYPE_2__ Texture; } ;
struct TYPE_8__ {struct gl_texture_image** Image; } ;
typedef  scalar_t__ GLsizei ;
typedef  size_t GLint ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 scalar_t__ GL_TEXTURE_1D ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_3__*) ; 
 size_t MAX_TEXTURE_LEVELS ; 
 int /*<<< orphan*/  copy_tex_sub_image (TYPE_3__*,struct gl_texture_image*,scalar_t__,int,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

void gl_CopyTexSubImage1D( GLcontext *ctx,
                              GLenum target, GLint level,
                              GLint xoffset, GLint x, GLint y, GLsizei width )
{
   struct gl_texture_image *teximage;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glCopyTexSubImage1D" );
      return;
   }
   if (target!=GL_TEXTURE_1D) {
      gl_error( ctx, GL_INVALID_ENUM, "glCopyTexSubImage1D(target)" );
      return;
   }
   if (level<0 || level>=MAX_TEXTURE_LEVELS) {
      gl_error( ctx, GL_INVALID_VALUE, "glCopyTexSubImage1D(level)" );
      return;
   }
   if (width<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glCopyTexSubImage1D(width)" );
      return;
   }

   teximage = ctx->Texture.Current1D->Image[level];

   if (teximage) {
      if (xoffset < -((GLint)teximage->Border)) {
         gl_error( ctx, GL_INVALID_VALUE, "glCopyTexSubImage1D(xoffset)" );
         return;
      }
      /* NOTE: we're adding the border here, not subtracting! */
      if (xoffset+width > teximage->Width+teximage->Border) {
         gl_error( ctx, GL_INVALID_VALUE,
                   "glCopyTexSubImage1D(xoffset+width)" );
         return;
      }
      if (teximage->Data) {
         copy_tex_sub_image( ctx, teximage, width, 1, x, y, xoffset, 0);
      }
   }
   else {
      gl_error( ctx, GL_INVALID_OPERATION, "glCopyTexSubImage1D" );
   }
}