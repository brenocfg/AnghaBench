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
struct TYPE_3__ {int EaNameLength; scalar_t__ EaValueLength; scalar_t__ EaName; int /*<<< orphan*/  Flags; int /*<<< orphan*/  NextEntryOffset; } ;
typedef  TYPE_1__* PFILE_FULL_EA_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DbgP (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  print_hexbuf (int /*<<< orphan*/ ,unsigned char*,unsigned char*,scalar_t__) ; 

void print_ea_info(int on, PFILE_FULL_EA_INFORMATION info)
{
    if (!on) return;
    DbgP("FULL_EA_INFO: NextOffset=%d Flags=%x EaNameLength=%d "
        "ExValueLength=%x EaName=%s\n", info->NextEntryOffset, info->Flags,
        info->EaNameLength, info->EaValueLength, info->EaName);
    if (info->EaValueLength) 
        print_hexbuf(0, (unsigned char *)"eavalue", 
            (unsigned char *)info->EaName + info->EaNameLength + 1, 
            info->EaValueLength);
}