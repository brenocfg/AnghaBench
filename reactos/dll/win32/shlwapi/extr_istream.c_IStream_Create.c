#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_1__ IStream_iface; scalar_t__ grfStateBits; scalar_t__ type; int /*<<< orphan*/  lpszPath; int /*<<< orphan*/  dwMode; int /*<<< orphan*/  hFile; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ IStream ;
typedef  TYPE_2__ ISHFileStream ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHLWAPI_fsVTable ; 
 int /*<<< orphan*/  StrDupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 

__attribute__((used)) static IStream *IStream_Create(LPCWSTR lpszPath, HANDLE hFile, DWORD dwMode)
{
    ISHFileStream *fileStream;

    fileStream = HeapAlloc(GetProcessHeap(), 0, sizeof(ISHFileStream));
    if (!fileStream) return NULL;

    fileStream->IStream_iface.lpVtbl = &SHLWAPI_fsVTable;
    fileStream->ref = 1;
    fileStream->hFile = hFile;
    fileStream->dwMode = dwMode;
    fileStream->lpszPath = StrDupW(lpszPath);
    fileStream->type = 0; /* FIXME */
    fileStream->grfStateBits = 0; /* FIXME */

    TRACE ("Returning %p\n", fileStream);
    return &fileStream->IStream_iface;
}