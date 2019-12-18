#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* lpstrCustomFilter; void* lpstrFile; void* lpstrFileTitle; scalar_t__ lpTemplateName; scalar_t__ lpstrTitle; scalar_t__ lpstrInitialDir; scalar_t__ lpstrFilter; } ;
typedef  TYPE_1__ OPENFILENAMEW ;

/* Variables and functions */
 int /*<<< orphan*/  IS_INTRESOURCE (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (void*) ; 

__attribute__((used)) static void FD31_FreeOfnW(OPENFILENAMEW *ofnW)
{
    heap_free((void *)ofnW->lpstrFilter);
    heap_free(ofnW->lpstrCustomFilter);
    heap_free(ofnW->lpstrFile);
    heap_free(ofnW->lpstrFileTitle);
    heap_free((void *)ofnW->lpstrInitialDir);
    heap_free((void *)ofnW->lpstrTitle);
    if (!IS_INTRESOURCE(ofnW->lpTemplateName))
        heap_free((void *)ofnW->lpTemplateName);
}