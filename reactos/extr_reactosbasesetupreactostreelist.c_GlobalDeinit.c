#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hDefaultFontB ; 
 int /*<<< orphan*/ * hDefaultFontN ; 
 int /*<<< orphan*/ * hPatternPen ; 
 int /*<<< orphan*/  lWindowCount ; 
 int /*<<< orphan*/  pBufferedPtExit () ; 

__attribute__((used)) static void GlobalDeinit() {

	int	lCount;

	lCount = InterlockedDecrement(&lWindowCount);
	if(lCount >= 0)
		return;

	if(hDefaultFontN) {
		DeleteObject(hDefaultFontN);
		hDefaultFontN = NULL;
	}

	if(hDefaultFontB) {
		DeleteObject(hDefaultFontB);
		hDefaultFontB = NULL;
	}

	if(hPatternPen) {
		DeleteObject(hPatternPen);
		hPatternPen = NULL;
	}

	if(pBufferedPtExit) {
		pBufferedPtExit();
	}

}