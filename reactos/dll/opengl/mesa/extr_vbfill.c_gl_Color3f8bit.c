#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ColorMaterialEnabled; } ;
struct TYPE_8__ {int* ByteColor; } ;
struct TYPE_9__ {TYPE_2__* VB; TYPE_1__ Light; TYPE_3__ Current; } ;
struct TYPE_7__ {int /*<<< orphan*/  MonoColor; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FLOAT_COLOR_TO_UBYTE_COLOR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FALSE ; 

void gl_Color3f8bit( GLcontext *ctx, GLfloat red, GLfloat green, GLfloat blue )
{
   FLOAT_COLOR_TO_UBYTE_COLOR(ctx->Current.ByteColor[0], red);
   FLOAT_COLOR_TO_UBYTE_COLOR(ctx->Current.ByteColor[1], green);
   FLOAT_COLOR_TO_UBYTE_COLOR(ctx->Current.ByteColor[2], blue);
   ctx->Current.ByteColor[3] = 255;
   ASSERT( !ctx->Light.ColorMaterialEnabled );
   ctx->VB->MonoColor = GL_FALSE;
}