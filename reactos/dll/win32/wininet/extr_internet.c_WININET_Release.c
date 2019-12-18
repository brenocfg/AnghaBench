#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ htype; int dwInternalFlags; scalar_t__ hInternet; TYPE_1__* vtbl; int /*<<< orphan*/  entry; int /*<<< orphan*/  dwContext; int /*<<< orphan*/  refs; } ;
typedef  TYPE_2__ object_header_t ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  size_t UINT_PTR ;
struct TYPE_10__ {int /*<<< orphan*/  (* Destroy ) (TYPE_2__*) ;int /*<<< orphan*/  (* CloseConnection ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int INET_OPENURL ; 
 int /*<<< orphan*/  INTERNET_STATUS_HANDLE_CLOSING ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WH_HFTPSESSION ; 
 scalar_t__ WH_HHTTPSESSION ; 
 scalar_t__ WH_HINIT ; 
 int /*<<< orphan*/  WININET_cs ; 
 int /*<<< orphan*/ ** handle_table ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  invalidate_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 size_t next_handle ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

BOOL WININET_Release( object_header_t *info )
{
    ULONG refs = InterlockedDecrement(&info->refs);
    TRACE( "object %p refcount = %d\n", info, refs );
    if( !refs )
    {
        invalidate_handle(info);
        if ( info->vtbl->CloseConnection )
        {
            TRACE( "closing connection %p\n", info);
            info->vtbl->CloseConnection( info );
        }
        /* Don't send a callback if this is a session handle created with InternetOpenUrl */
        if ((info->htype != WH_HHTTPSESSION && info->htype != WH_HFTPSESSION)
            || !(info->dwInternalFlags & INET_OPENURL))
        {
            INTERNET_SendCallback(info, info->dwContext,
                                  INTERNET_STATUS_HANDLE_CLOSING, &info->hInternet,
                                  sizeof(HINTERNET));
        }
        TRACE( "destroying object %p\n", info);
        if ( info->htype != WH_HINIT )
            list_remove( &info->entry );
        info->vtbl->Destroy( info );

        if(info->hInternet) {
            UINT_PTR handle = (UINT_PTR)info->hInternet;

            EnterCriticalSection( &WININET_cs );

            handle_table[handle] = NULL;
            if(next_handle > handle)
                next_handle = handle;

            LeaveCriticalSection( &WININET_cs );
        }

        heap_free(info);
    }
    return TRUE;
}