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
struct TYPE_5__ {void* EdgeFlagEnabled; void* TexCoordEnabled; void* IndexEnabled; void* ColorEnabled; void* NormalEnabled; void* VertexEnabled; } ;
struct TYPE_6__ {TYPE_1__ Array; } ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;
typedef  void* GLboolean ;

/* Variables and functions */
#define  GL_COLOR_ARRAY 133 
#define  GL_EDGE_FLAG_ARRAY 132 
#define  GL_INDEX_ARRAY 131 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_NORMAL_ARRAY 130 
#define  GL_TEXTURE_COORD_ARRAY 129 
#define  GL_VERTEX_ARRAY 128 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_client_state( GLcontext *ctx, GLenum cap, GLboolean state )
{
   switch (cap) {
      case GL_VERTEX_ARRAY:
         ctx->Array.VertexEnabled = state;
         break;
      case GL_NORMAL_ARRAY:
         ctx->Array.NormalEnabled = state;
         break;
      case GL_COLOR_ARRAY:
         ctx->Array.ColorEnabled = state;
         break;
      case GL_INDEX_ARRAY:
         ctx->Array.IndexEnabled = state;
         break;
      case GL_TEXTURE_COORD_ARRAY:
         ctx->Array.TexCoordEnabled = state;
         break;
      case GL_EDGE_FLAG_ARRAY:
         ctx->Array.EdgeFlagEnabled = state;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glEnable/DisableClientState" );
   }
}