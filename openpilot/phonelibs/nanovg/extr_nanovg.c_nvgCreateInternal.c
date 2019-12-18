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
typedef  int /*<<< orphan*/  fontParams ;
struct TYPE_12__ {scalar_t__ (* renderCreate ) (int /*<<< orphan*/ ) ;scalar_t__ (* renderCreateTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  userPtr; } ;
struct TYPE_13__ {scalar_t__* fontImages; float* commands; int ccommands; scalar_t__ fontImageIdx; void* height; void* width; TYPE_1__ params; int /*<<< orphan*/ * fs; int /*<<< orphan*/ * userPtr; int /*<<< orphan*/ * renderDelete; int /*<<< orphan*/ * renderDraw; int /*<<< orphan*/ * renderUpdate; int /*<<< orphan*/ * renderCreate; int /*<<< orphan*/  flags; int /*<<< orphan*/ * cache; scalar_t__ ncommands; } ;
typedef  TYPE_1__ NVGparams ;
typedef  TYPE_2__ NVGcontext ;
typedef  TYPE_2__ FONSparams ;

/* Variables and functions */
 int /*<<< orphan*/  FONS_ZERO_TOPLEFT ; 
 int NVG_INIT_COMMANDS_SIZE ; 
 void* NVG_INIT_FONTIMAGE_SIZE ; 
 int NVG_MAX_FONTIMAGES ; 
 int /*<<< orphan*/  NVG_TEXTURE_ALPHA ; 
 int /*<<< orphan*/ * fonsCreateInternal (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgDeleteInternal (TYPE_2__*) ; 
 int /*<<< orphan*/  nvgReset (TYPE_2__*) ; 
 int /*<<< orphan*/  nvgSave (TYPE_2__*) ; 
 int /*<<< orphan*/ * nvg__allocPathCache () ; 
 int /*<<< orphan*/  nvg__setDevicePixelRatio (TYPE_2__*,float) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

NVGcontext* nvgCreateInternal(NVGparams* params)
{
	FONSparams fontParams;
	NVGcontext* ctx = (NVGcontext*)malloc(sizeof(NVGcontext));
	int i;
	if (ctx == NULL) goto error;
	memset(ctx, 0, sizeof(NVGcontext));

	ctx->params = *params;
	for (i = 0; i < NVG_MAX_FONTIMAGES; i++)
		ctx->fontImages[i] = 0;

	ctx->commands = (float*)malloc(sizeof(float)*NVG_INIT_COMMANDS_SIZE);
	if (!ctx->commands) goto error;
	ctx->ncommands = 0;
	ctx->ccommands = NVG_INIT_COMMANDS_SIZE;

	ctx->cache = nvg__allocPathCache();
	if (ctx->cache == NULL) goto error;

	nvgSave(ctx);
	nvgReset(ctx);

	nvg__setDevicePixelRatio(ctx, 1.0f);

	if (ctx->params.renderCreate(ctx->params.userPtr) == 0) goto error;

	// Init font rendering
	memset(&fontParams, 0, sizeof(fontParams));
	fontParams.width = NVG_INIT_FONTIMAGE_SIZE;
	fontParams.height = NVG_INIT_FONTIMAGE_SIZE;
	fontParams.flags = FONS_ZERO_TOPLEFT;
	fontParams.renderCreate = NULL;
	fontParams.renderUpdate = NULL;
	fontParams.renderDraw = NULL;
	fontParams.renderDelete = NULL;
	fontParams.userPtr = NULL;
	ctx->fs = fonsCreateInternal(&fontParams);
	if (ctx->fs == NULL) goto error;

	// Create font texture
	ctx->fontImages[0] = ctx->params.renderCreateTexture(ctx->params.userPtr, NVG_TEXTURE_ALPHA, fontParams.width, fontParams.height, 0, NULL);
	if (ctx->fontImages[0] == 0) goto error;
	ctx->fontImageIdx = 0;

	return ctx;

error:
	nvgDeleteInternal(ctx);
	return 0;
}