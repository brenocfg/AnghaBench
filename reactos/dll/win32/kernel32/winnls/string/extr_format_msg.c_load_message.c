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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int Flags; scalar_t__ Text; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ MESSAGE_RESOURCE_ENTRY ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MESSAGE_RESOURCE_UNICODE ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ RT_MESSAGETABLE ; 
 int /*<<< orphan*/  RtlFindMessage (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const**) ; 
 int /*<<< orphan*/  RtlNtStatusToDosError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LPWSTR load_message( HMODULE module, UINT id, WORD lang )
{
#ifdef __REACTOS__
    MESSAGE_RESOURCE_ENTRY *mre;
#else
    const MESSAGE_RESOURCE_ENTRY *mre;
#endif
    WCHAR *buffer;
    NTSTATUS status;

    TRACE("module = %p, id = %08x\n", module, id );

    if (!module) module = GetModuleHandleW( NULL );
#ifdef __REACTOS__
    status = RtlFindMessage(module, (ULONG_PTR)RT_MESSAGETABLE, lang, id, &mre);
    if (!NT_SUCCESS(status))
#else
    if ((status = RtlFindMessage( module, RT_MESSAGETABLE, lang, id, &mre )) != STATUS_SUCCESS)
#endif
    {
        SetLastError( RtlNtStatusToDosError(status) );
        return NULL;
    }

    if (mre->Flags & MESSAGE_RESOURCE_UNICODE)
    {
        int len = (strlenW( (const WCHAR *)mre->Text ) + 1) * sizeof(WCHAR);
        if (!(buffer = HeapAlloc( GetProcessHeap(), 0, len ))) return NULL;
        memcpy( buffer, mre->Text, len );
    }
    else
    {
        int len = MultiByteToWideChar( CP_ACP, 0, (const char *)mre->Text, -1, NULL, 0 );
        if (!(buffer = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) ))) return NULL;
        MultiByteToWideChar( CP_ACP, 0, (const char*)mre->Text, -1, buffer, len );
    }
    TRACE("returning %s\n", wine_dbgstr_w(buffer));
    return buffer;
}