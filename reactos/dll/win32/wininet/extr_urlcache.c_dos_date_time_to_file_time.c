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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_4__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; } ;
typedef  TYPE_1__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  DosDateTimeToFileTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void dos_date_time_to_file_time(WORD fatdate, WORD fattime,
                                           FILETIME *ft)
{
    if (!fatdate && !fattime)
        ft->dwLowDateTime = ft->dwHighDateTime = 0;
    else
        DosDateTimeToFileTime(fatdate, fattime, ft);
}