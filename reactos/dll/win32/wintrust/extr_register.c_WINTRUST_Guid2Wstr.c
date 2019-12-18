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
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * Data4; int /*<<< orphan*/  Data3; int /*<<< orphan*/  Data2; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__ GUID ;

/* Variables and functions */
 int /*<<< orphan*/  wsprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void WINTRUST_Guid2Wstr(const GUID* pgActionID, WCHAR* GuidString)
{ 
    static const WCHAR wszFormat[] = {'{','%','0','8','l','X','-','%','0','4','X','-','%','0','4','X','-',
                                      '%','0','2','X','%','0','2','X','-','%','0','2','X','%','0','2','X','%','0','2','X','%','0','2',
                                      'X','%','0','2','X','%','0','2','X','}', 0};

    wsprintfW(GuidString, wszFormat, pgActionID->Data1, pgActionID->Data2, pgActionID->Data3,
        pgActionID->Data4[0], pgActionID->Data4[1], pgActionID->Data4[2], pgActionID->Data4[3],
        pgActionID->Data4[4], pgActionID->Data4[5], pgActionID->Data4[6], pgActionID->Data4[7]);
}