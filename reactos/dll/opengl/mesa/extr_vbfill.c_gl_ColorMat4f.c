#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ColorMaterialBitmask; int /*<<< orphan*/  ColorMaterialEnabled; } ;
struct TYPE_8__ {void** ByteColor; } ;
struct TYPE_12__ {TYPE_4__* VB; TYPE_3__ Light; TYPE_2__* Visual; TYPE_1__ Current; } ;
struct TYPE_11__ {int /*<<< orphan*/  MonoColor; } ;
struct TYPE_9__ {int RedScale; int GreenScale; int BlueScale; int AlphaScale; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_5__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSIGN_4V (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CLAMP (int /*<<< orphan*/ ,float,float) ; 
 void* FloatToInt (int) ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  gl_set_material (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gl_ColorMat4f( GLcontext *ctx,
                    GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
   GLfloat color[4];
   ctx->Current.ByteColor[0] = FloatToInt(CLAMP(red  , 0.0F, 1.0F) * ctx->Visual->RedScale);
   ctx->Current.ByteColor[1] = FloatToInt(CLAMP(green, 0.0F, 1.0F) * ctx->Visual->GreenScale);
   ctx->Current.ByteColor[2] = FloatToInt(CLAMP(blue , 0.0F, 1.0F) * ctx->Visual->BlueScale);
   ctx->Current.ByteColor[3] = FloatToInt(CLAMP(alpha, 0.0F, 1.0F) * ctx->Visual->AlphaScale);
   /* update material */
   ASSERT( ctx->Light.ColorMaterialEnabled );
   ASSIGN_4V( color, red, green, blue, alpha );
   gl_set_material( ctx, ctx->Light.ColorMaterialBitmask, color );
   ctx->VB->MonoColor = GL_FALSE;
}