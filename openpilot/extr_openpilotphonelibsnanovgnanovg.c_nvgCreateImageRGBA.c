#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* renderCreateTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,unsigned char const*) ;int /*<<< orphan*/  userPtr; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
typedef  TYPE_2__ NVGcontext ;

/* Variables and functions */
 int /*<<< orphan*/  NVG_TEXTURE_RGBA ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,unsigned char const*) ; 

int nvgCreateImageRGBA(NVGcontext* ctx, int w, int h, int imageFlags, const unsigned char* data)
{
	return ctx->params.renderCreateTexture(ctx->params.userPtr, NVG_TEXTURE_RGBA, w, h, imageFlags, data);
}