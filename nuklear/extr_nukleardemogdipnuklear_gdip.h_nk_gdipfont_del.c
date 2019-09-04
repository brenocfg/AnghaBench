#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ GdipFont ;

/* Variables and functions */
 int /*<<< orphan*/  GdipDeleteFont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
nk_gdipfont_del(GdipFont *font)
{
    if(!font) return;
    GdipDeleteFont(font->handle);
    free(font);
}