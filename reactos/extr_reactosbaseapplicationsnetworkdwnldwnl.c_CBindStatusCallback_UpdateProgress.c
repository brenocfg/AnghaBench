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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_3__ {int Size; int Progress; } ;
typedef  TYPE_1__ CBindStatusCallback ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_BYTES_DOWNLOADED ; 
 int /*<<< orphan*/  IDS_BYTES_DOWNLOADED_FULL ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  write_status (int /*<<< orphan*/ *,int,...) ; 

__attribute__((used)) static void
CBindStatusCallback_UpdateProgress(CBindStatusCallback *This)
{
    WCHAR szMessage[MAX_PATH];

    /* FIXME: better output */
    if (This->Size != 0)
    {
        UINT Percentage;

        Percentage = (UINT)((This->Progress * 100) / This->Size);
        if (Percentage > 99)
            Percentage = 99;

        LoadStringW(NULL, IDS_BYTES_DOWNLOADED_FULL, szMessage, ARRAYSIZE(szMessage));

        write_status(szMessage, Percentage, This->Progress);
    }
    else
    {
        LoadStringW(NULL, IDS_BYTES_DOWNLOADED, szMessage, ARRAYSIZE(szMessage));

        /* Unknown size */
        write_status(szMessage, This->Progress);
    }
}