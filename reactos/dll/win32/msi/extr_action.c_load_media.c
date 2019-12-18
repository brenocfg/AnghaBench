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
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {TYPE_1__* db; } ;
struct TYPE_6__ {int /*<<< orphan*/  storage; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  TYPE_2__* LPVOID ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_INITIAL_MEDIA_TRANSFORM_DISKID ; 
 scalar_t__ MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 char* MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 scalar_t__ msi_add_cabinet_stream (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static UINT load_media( MSIRECORD *row, LPVOID param )
{
    MSIPACKAGE *package = param;
    UINT disk_id = MSI_RecordGetInteger( row, 1 );
    const WCHAR *cabinet = MSI_RecordGetString( row, 4 );

    /* FIXME: load external cabinets and directory sources too */
    if (!cabinet || cabinet[0] != '#' || disk_id >= MSI_INITIAL_MEDIA_TRANSFORM_DISKID)
        return ERROR_SUCCESS;

    return msi_add_cabinet_stream( package, disk_id, package->db->storage, cabinet );
}