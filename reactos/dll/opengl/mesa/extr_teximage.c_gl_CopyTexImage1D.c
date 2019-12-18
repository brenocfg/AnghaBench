#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gl_image {int dummy; } ;
typedef  int GLsizei ;
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLenum ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 int /*<<< orphan*/  GL_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  GL_RGBA ; 
 scalar_t__ GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 scalar_t__ INSIDE_BEGIN_END (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_TEXTURE_LEVELS ; 
 int MAX_TEXTURE_SIZE ; 
 scalar_t__ decode_internal_format (scalar_t__) ; 
 int /*<<< orphan*/  gl_TexImage1D (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gl_image*) ; 
 int /*<<< orphan*/  gl_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct gl_image* read_color_image (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int,scalar_t__) ; 

void gl_CopyTexImage1D( GLcontext *ctx,
                        GLenum target, GLint level,
                        GLenum internalformat,
                        GLint x, GLint y,
                        GLsizei width, GLint border )
{
   GLint format;
   struct gl_image *teximage;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glCopyTexImage1D" );
      return;
   }
   if (target!=GL_TEXTURE_1D) {
      gl_error( ctx, GL_INVALID_ENUM, "glCopyTexImage1D(target)" );
      return;
   }
   if (level<0 || level>=MAX_TEXTURE_LEVELS) {
      gl_error( ctx, GL_INVALID_VALUE, "glCopyTexImage1D(level)" );
      return;
   }
   if (border!=0 && border!=1) {
      gl_error( ctx, GL_INVALID_VALUE, "glCopyTexImage1D(border)" );
      return;
   }
   if (width<2*border || width>2+MAX_TEXTURE_SIZE || width<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glCopyTexImage1D(width)" );
      return;
   }
   format = decode_internal_format( internalformat );
   if (format<0 || (internalformat>=1 && internalformat<=4)) {
      gl_error( ctx, GL_INVALID_VALUE, "glCopyTexImage1D(format)" );
      return;
   }

   teximage = read_color_image( ctx, x, y, width, 1, format );
   if (!teximage) {
      gl_error( ctx, GL_OUT_OF_MEMORY, "glCopyTexImage1D" );
      return;
   }

   gl_TexImage1D( ctx, target, level, internalformat, width,
                  border, GL_RGBA, GL_UNSIGNED_BYTE, teximage );

   /* teximage was freed in gl_TexImage1D */
}