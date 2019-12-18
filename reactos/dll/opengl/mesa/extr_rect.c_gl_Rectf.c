#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* Vertex2f ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {TYPE_1__ Exec; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_QUADS ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_Begin (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_End (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gl_Rectf( GLcontext *ctx, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 )
{
   /*
    * TODO: we could examine a bunch of state variables and ultimately
    * call the Driver->RectFunc() function to draw a screen-aligned
    * filled rectangle.  Someday...
    */

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glRect" );
      return;
   }
   gl_Begin( ctx, GL_QUADS );
   (*ctx->Exec.Vertex2f)( ctx, x1, y1 );
   (*ctx->Exec.Vertex2f)( ctx, x2, y1 );
   (*ctx->Exec.Vertex2f)( ctx, x2, y2 );
   (*ctx->Exec.Vertex2f)( ctx, x1, y2 );
   gl_End( ctx );
}