#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void** Image; } ;
struct TYPE_5__ {TYPE_3__* Proxy2D; TYPE_3__* Proxy1D; } ;
struct TYPE_6__ {TYPE_1__ Texture; } ;
typedef  size_t GLint ;
typedef  TYPE_2__ GLcontext ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 scalar_t__ GL_FALSE ; 
 scalar_t__ GL_TRUE ; 
 size_t MAX_TEXTURE_LEVELS ; 
 void* gl_alloc_texture_image () ; 
 void* gl_alloc_texture_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_free_texture_image (void*) ; 
 int /*<<< orphan*/  gl_free_texture_object (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static GLboolean alloc_proxy_textures( GLcontext *ctx )
{
   GLboolean out_of_memory;
   GLint i;

   ctx->Texture.Proxy1D = gl_alloc_texture_object(NULL, 0, 1);
   if (!ctx->Texture.Proxy1D) {
      return GL_FALSE;
   }

   ctx->Texture.Proxy2D = gl_alloc_texture_object(NULL, 0, 2);
   if (!ctx->Texture.Proxy2D) {
      gl_free_texture_object(NULL, ctx->Texture.Proxy1D);
      return GL_FALSE;
   }

   out_of_memory = GL_FALSE;
   for (i=0;i<MAX_TEXTURE_LEVELS;i++) {
      ctx->Texture.Proxy1D->Image[i] = gl_alloc_texture_image();
      ctx->Texture.Proxy2D->Image[i] = gl_alloc_texture_image();
      if (!ctx->Texture.Proxy1D->Image[i]
          || !ctx->Texture.Proxy2D->Image[i]) {
         out_of_memory = GL_TRUE;
      }
   }
   if (out_of_memory) {
      for (i=0;i<MAX_TEXTURE_LEVELS;i++) {
         if (ctx->Texture.Proxy1D->Image[i]) {
            gl_free_texture_image(ctx->Texture.Proxy1D->Image[i]);
         }
         if (ctx->Texture.Proxy2D->Image[i]) {
            gl_free_texture_image(ctx->Texture.Proxy2D->Image[i]);
         }
      }
      gl_free_texture_object(NULL, ctx->Texture.Proxy1D);
      gl_free_texture_object(NULL, ctx->Texture.Proxy2D);
      return GL_FALSE;
   }
   else {
      return GL_TRUE;
   }
}