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
struct TYPE_4__ {int /*<<< orphan*/ * NextStyle; int /*<<< orphan*/ * ChildStyle; struct TYPE_4__* StyleName; int /*<<< orphan*/ * DisplayName; } ;
typedef  int /*<<< orphan*/  THEME_STYLE ;
typedef  TYPE_1__* PTHEME_STYLE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 void* _wcsdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static PTHEME_STYLE
CreateStyle(LPCWSTR pszName, LPCWSTR pszDisplayName)
{
    PTHEME_STYLE pStyle;

    pStyle = (PTHEME_STYLE) malloc(sizeof(THEME_STYLE));
    if (pStyle == NULL) return NULL;

    pStyle->StyleName = _wcsdup(pszName);
    if (pStyle->StyleName == NULL)
    {
        free(pStyle);
        return NULL;
    }

    pStyle->DisplayName = _wcsdup(pszDisplayName);
    if (pStyle->DisplayName == NULL)
    {
        free(pStyle->StyleName);
        free(pStyle);
        return NULL;
    }

    pStyle->ChildStyle = NULL;
    pStyle->NextStyle = NULL;

    return pStyle;
}