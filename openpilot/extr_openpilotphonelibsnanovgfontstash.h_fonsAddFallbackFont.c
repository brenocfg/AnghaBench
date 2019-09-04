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
struct TYPE_5__ {TYPE_1__** fonts; } ;
struct TYPE_4__ {scalar_t__ nfallbacks; int* fallbacks; } ;
typedef  TYPE_1__ FONSfont ;
typedef  TYPE_2__ FONScontext ;

/* Variables and functions */
 scalar_t__ FONS_MAX_FALLBACKS ; 

int fonsAddFallbackFont(FONScontext* stash, int base, int fallback)
{
	FONSfont* baseFont = stash->fonts[base];
	if (baseFont->nfallbacks < FONS_MAX_FALLBACKS) {
		baseFont->fallbacks[baseFont->nfallbacks++] = fallback;
		return 1;
	}
	return 0;
}