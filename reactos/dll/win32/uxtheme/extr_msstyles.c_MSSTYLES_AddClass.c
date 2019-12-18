#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * overrides; int /*<<< orphan*/ * partstate; struct TYPE_9__* next; int /*<<< orphan*/  szClassName; int /*<<< orphan*/  szAppName; int /*<<< orphan*/  hTheme; } ;
struct TYPE_8__ {TYPE_2__* classes; int /*<<< orphan*/  hTheme; } ;
typedef  int /*<<< orphan*/  THEME_CLASS ;
typedef  TYPE_1__* PTHEME_FILE ;
typedef  TYPE_2__* PTHEME_CLASS ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* MSSTYLES_FindClass (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PTHEME_CLASS MSSTYLES_AddClass(PTHEME_FILE tf, LPCWSTR pszAppName, LPCWSTR pszClassName)
{
    PTHEME_CLASS cur = MSSTYLES_FindClass(tf, pszAppName, pszClassName);
    if(cur) return cur;

    cur = HeapAlloc(GetProcessHeap(), 0, sizeof(THEME_CLASS));
    cur->hTheme = tf->hTheme;
    lstrcpyW(cur->szAppName, pszAppName);
    lstrcpyW(cur->szClassName, pszClassName);
    cur->next = tf->classes;
    cur->partstate = NULL;
    cur->overrides = NULL;
    tf->classes = cur;
    return cur;
}