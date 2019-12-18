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
struct TYPE_6__ {scalar_t__ Clear; } ;
struct TYPE_7__ {TYPE_1__ Depth; } ;
typedef  scalar_t__ GLfloat ;
typedef  TYPE_2__ GLcontext ;
typedef  int /*<<< orphan*/  GLclampd ;

/* Variables and functions */
 scalar_t__ CLAMP (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_ClearDepth( GLcontext* ctx, GLclampd depth )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glClearDepth" );
      return;
   }
   ctx->Depth.Clear = (GLfloat) CLAMP( depth, 0.0, 1.0 );
}