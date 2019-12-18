#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ActivateAtStorage; int RunAsInteractiveUser; int /*<<< orphan*/  entry; void* DllSurrogate; void* ServiceParameters; void* LocalServer; int /*<<< orphan*/  RemoteServerName; void* AppID; } ;
struct TYPE_7__ {int /*<<< orphan*/  appids; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIAPPID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSI_RecordIsNull (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  deformat_string (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static MSIAPPID *load_appid( MSIPACKAGE* package, MSIRECORD *row )
{
    LPCWSTR buffer;
    MSIAPPID *appid;

    /* fill in the data */

    appid = msi_alloc_zero( sizeof(MSIAPPID) );
    if (!appid)
        return NULL;
    
    appid->AppID = msi_dup_record_field( row, 1 );
    TRACE("loading appid %s\n", debugstr_w( appid->AppID ));

    buffer = MSI_RecordGetString(row,2);
    deformat_string( package, buffer, &appid->RemoteServerName );

    appid->LocalServer = msi_dup_record_field(row,3);
    appid->ServiceParameters = msi_dup_record_field(row,4);
    appid->DllSurrogate = msi_dup_record_field(row,5);

    appid->ActivateAtStorage = !MSI_RecordIsNull(row,6);
    appid->RunAsInteractiveUser = !MSI_RecordIsNull(row,7);

    list_add_tail( &package->appids, &appid->entry );
    
    return appid;
}