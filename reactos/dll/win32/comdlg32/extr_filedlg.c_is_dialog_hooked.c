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
struct TYPE_5__ {TYPE_1__* ofnInfos; } ;
struct TYPE_4__ {int Flags; scalar_t__ lpfnHook; } ;
typedef  TYPE_2__ FileOpenDlgInfos ;
typedef  int BOOL ;

/* Variables and functions */
 int OFN_ENABLEHOOK ; 

__attribute__((used)) static BOOL is_dialog_hooked(const FileOpenDlgInfos *info)
{
    return (info->ofnInfos->Flags & OFN_ENABLEHOOK) && info->ofnInfos->lpfnHook;
}