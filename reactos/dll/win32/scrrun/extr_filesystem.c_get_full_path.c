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
struct TYPE_3__ {int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  char* BSTR ;

/* Variables and functions */
 int MAX_PATH ; 
 char* SysAllocString (int /*<<< orphan*/ *) ; 
 int SysStringLen (char*) ; 
 int /*<<< orphan*/  bsW ; 
 int /*<<< orphan*/  strcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static BSTR get_full_path(BSTR path, const WIN32_FIND_DATAW *data)
{
    int len = SysStringLen(path);
    WCHAR buffW[MAX_PATH];

    strcpyW(buffW, path);
    if (path[len-1] != '\\')
        strcatW(buffW, bsW);
    strcatW(buffW, data->cFileName);

    return SysAllocString(buffW);
}