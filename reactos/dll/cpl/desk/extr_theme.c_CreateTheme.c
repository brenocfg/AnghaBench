#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* DisplayName; int /*<<< orphan*/ * ThemeFileName; int /*<<< orphan*/ * SizesList; int /*<<< orphan*/ * NextTheme; int /*<<< orphan*/ * ColoursList; } ;
typedef  TYPE_1__ THEME ;
typedef  TYPE_1__* PTHEME ;
typedef  int /*<<< orphan*/ * LPCWSTR ;

/* Variables and functions */
 void* _wcsdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static THEME*
CreateTheme(LPCWSTR pszName, LPCWSTR pszDisplayName)
{
    PTHEME pTheme;

    pTheme = (PTHEME) malloc(sizeof(THEME));
    if (pTheme == NULL) return NULL;

    pTheme->DisplayName = _wcsdup(pszDisplayName);
    if (pTheme->DisplayName == NULL)
    {
        free(pTheme);
        return NULL;
    }

    pTheme->ColoursList = NULL;
    pTheme->NextTheme = NULL;
    pTheme->SizesList = NULL;

    if (pszName == NULL)
    {
        pTheme->ThemeFileName = NULL;
        return pTheme;
    }

    pTheme->ThemeFileName = _wcsdup(pszName);
    if (pTheme->ThemeFileName == NULL)
    {
        free(pTheme->DisplayName);
        free(pTheme);
        return NULL;
    }

    return pTheme;
}