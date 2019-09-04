#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pages_shown; } ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__ preview ; 
 int /*<<< orphan*/  var_previewpages ; 

void registry_read_previewpages(HKEY hKey)
{
    DWORD size = sizeof(DWORD);
    if(!hKey ||
       RegQueryValueExW(hKey, var_previewpages, 0, NULL,
                        (LPBYTE)&preview.pages_shown, &size) != ERROR_SUCCESS ||
       size != sizeof(DWORD))
    {
        preview.pages_shown = 1;
    } else {
        if (preview.pages_shown < 1) preview.pages_shown = 1;
        else if (preview.pages_shown > 2) preview.pages_shown = 2;
    }
}