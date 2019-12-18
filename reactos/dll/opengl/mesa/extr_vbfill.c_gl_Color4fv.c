#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ColorMaterialEnabled; } ;
struct TYPE_7__ {void** ByteColor; } ;
struct TYPE_11__ {TYPE_4__* VB; TYPE_3__ Light; TYPE_2__* Visual; TYPE_1__ Current; } ;
struct TYPE_10__ {int /*<<< orphan*/  MonoColor; } ;
struct TYPE_8__ {int RedScale; int GreenScale; int BlueScale; int AlphaScale; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_5__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CLAMP (int /*<<< orphan*/  const,float,float) ; 
 void* FloatToInt (int) ; 
 int /*<<< orphan*/  GL_FALSE ; 

void gl_Color4fv( GLcontext *ctx, const GLfloat *c )
{
   ctx->Current.ByteColor[0] = FloatToInt(CLAMP(c[0], 0.0F, 1.0F) * ctx->Visual->RedScale);
   ctx->Current.ByteColor[1] = FloatToInt(CLAMP(c[1], 0.0F, 1.0F) * ctx->Visual->GreenScale);
   ctx->Current.ByteColor[2] = FloatToInt(CLAMP(c[2], 0.0F, 1.0F) * ctx->Visual->BlueScale);
   ctx->Current.ByteColor[3] = FloatToInt(CLAMP(c[3], 0.0F, 1.0F) * ctx->Visual->AlphaScale);
   ASSERT( !ctx->Light.ColorMaterialEnabled );
   ctx->VB->MonoColor = GL_FALSE;
}