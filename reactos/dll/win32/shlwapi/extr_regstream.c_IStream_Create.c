#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * keyNameA; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; int /*<<< orphan*/  bUnicode; TYPE_1__ u; int /*<<< orphan*/  dwMode; scalar_t__ dwPos; int /*<<< orphan*/  dwLength; int /*<<< orphan*/  pbBuffer; int /*<<< orphan*/  hKey; TYPE_2__ IStream_iface; } ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  TYPE_3__ ISHRegStream ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STGM_READWRITE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  rstvt ; 

__attribute__((used)) static ISHRegStream *IStream_Create(HKEY hKey, LPBYTE pbBuffer, DWORD dwLength)
{
 ISHRegStream* regStream;

 regStream = HeapAlloc(GetProcessHeap(), 0, sizeof(ISHRegStream));

 if (regStream)
 {
   regStream->IStream_iface.lpVtbl = &rstvt;
   regStream->ref = 1;
   regStream->hKey = hKey;
   regStream->pbBuffer = pbBuffer;
   regStream->dwLength = dwLength;
   regStream->dwPos = 0;
   regStream->dwMode = STGM_READWRITE;
   regStream->u.keyNameA = NULL;
   regStream->bUnicode = FALSE;
 }
 TRACE ("Returning %p\n", regStream);
 return regStream;
}