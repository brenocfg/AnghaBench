#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ColorMask; } ;
struct TYPE_7__ {int /*<<< orphan*/  NewState; TYPE_1__ Color; } ;
typedef  TYPE_2__ GLcontext ;
typedef  int GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_RASTER_OPS ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_ColorMask( GLcontext *ctx, GLboolean red, GLboolean green,
                   GLboolean blue, GLboolean alpha )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glColorMask" );
      return;
   }
   ctx->Color.ColorMask = (red << 3) | (green << 2) | (blue << 1) | alpha;
   ctx->NewState |= NEW_RASTER_OPS;
}