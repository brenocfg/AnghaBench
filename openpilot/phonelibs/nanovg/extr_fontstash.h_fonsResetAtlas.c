#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* renderResize ) (int /*<<< orphan*/ ,int,int) ;int width; int height; int /*<<< orphan*/  userPtr; } ;
struct TYPE_9__ {unsigned char* texData; int* dirtyRect; int nfonts; float itw; float ith; TYPE_1__ params; TYPE_2__** fonts; int /*<<< orphan*/  atlas; } ;
struct TYPE_8__ {int* lut; scalar_t__ nglyphs; } ;
typedef  TYPE_2__ FONSfont ;
typedef  TYPE_3__ FONScontext ;

/* Variables and functions */
 int FONS_HASH_LUT_SIZE ; 
 int /*<<< orphan*/  fons__addWhiteRect (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  fons__atlasReset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fons__flush (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (unsigned char*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,int) ; 

int fonsResetAtlas(FONScontext* stash, int width, int height)
{
	int i, j;
	if (stash == NULL) return 0;

	// Flush pending glyphs.
	fons__flush(stash);

	// Create new texture
	if (stash->params.renderResize != NULL) {
		if (stash->params.renderResize(stash->params.userPtr, width, height) == 0)
			return 0;
	}

	// Reset atlas
	fons__atlasReset(stash->atlas, width, height);

	// Clear texture data.
	stash->texData = (unsigned char*)realloc(stash->texData, width * height);
	if (stash->texData == NULL) return 0;
	memset(stash->texData, 0, width * height);

	// Reset dirty rect
	stash->dirtyRect[0] = width;
	stash->dirtyRect[1] = height;
	stash->dirtyRect[2] = 0;
	stash->dirtyRect[3] = 0;

	// Reset cached glyphs
	for (i = 0; i < stash->nfonts; i++) {
		FONSfont* font = stash->fonts[i];
		font->nglyphs = 0;
		for (j = 0; j < FONS_HASH_LUT_SIZE; j++)
			font->lut[j] = -1;
	}

	stash->params.width = width;
	stash->params.height = height;
	stash->itw = 1.0f/stash->params.width;
	stash->ith = 1.0f/stash->params.height;

	// Add white rect at 0,0 for debug drawing.
	fons__addWhiteRect(stash, 2,2);

	return 1;
}