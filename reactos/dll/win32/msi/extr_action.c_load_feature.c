#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* feature; TYPE_3__* package; } ;
typedef  TYPE_1__ _ilfs ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {void* Feature; int /*<<< orphan*/  entry; void* ActionRequest; void* Action; void* Installed; void* Attributes; void* Directory; void* Level; void* Display; void* Description; void* Title; void* Feature_Parent; int /*<<< orphan*/  Components; int /*<<< orphan*/  Children; } ;
struct TYPE_13__ {int /*<<< orphan*/  db; int /*<<< orphan*/  features; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdr; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  TYPE_3__ MSIPACKAGE ;
typedef  TYPE_4__ MSIFEATURE ;
typedef  TYPE_3__* LPVOID ;

/* Variables and functions */
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 void* INSTALLSTATE_UNKNOWN ; 
 scalar_t__ MSI_IterateRecords (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_2__**,char const*,void*) ; 
 void* MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSI_RecordIsNull (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  iterate_load_featurecomponents ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* msi_alloc_zero (int) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT load_feature(MSIRECORD * row, LPVOID param)
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','`','C','o','m','p','o','n','e','n','t','_','`',
         ' ','F','R','O','M',' ','`','F','e','a','t','u','r','e',
         'C','o','m','p','o','n','e','n','t','s','`',' ','W','H','E','R','E',' ',
         '`','F','e', 'a','t','u','r','e','_','`',' ','=','\'','%','s','\'',0};
    MSIPACKAGE *package = param;
    MSIFEATURE *feature;
    MSIQUERY *view;
    _ilfs ilfs;
    UINT rc;

    /* fill in the data */

    feature = msi_alloc_zero( sizeof (MSIFEATURE) );
    if (!feature)
        return ERROR_NOT_ENOUGH_MEMORY;

    list_init( &feature->Children );
    list_init( &feature->Components );
    
    feature->Feature = msi_dup_record_field( row, 1 );

    TRACE("Loading feature %s\n",debugstr_w(feature->Feature));

    feature->Feature_Parent = msi_dup_record_field( row, 2 );
    feature->Title = msi_dup_record_field( row, 3 );
    feature->Description = msi_dup_record_field( row, 4 );

    if (!MSI_RecordIsNull(row,5))
        feature->Display = MSI_RecordGetInteger(row,5);
  
    feature->Level= MSI_RecordGetInteger(row,6);
    feature->Directory = msi_dup_record_field( row, 7 );
    feature->Attributes = MSI_RecordGetInteger(row,8);

    feature->Installed = INSTALLSTATE_UNKNOWN;
    feature->Action = INSTALLSTATE_UNKNOWN;
    feature->ActionRequest = INSTALLSTATE_UNKNOWN;

    list_add_tail( &package->features, &feature->entry );

    /* load feature components */

    rc = MSI_OpenQuery( package->db, &view, query, feature->Feature );
    if (rc != ERROR_SUCCESS)
        return ERROR_SUCCESS;

    ilfs.package = package;
    ilfs.feature = feature;

    rc = MSI_IterateRecords(view, NULL, iterate_load_featurecomponents , &ilfs);
    msiobj_release(&view->hdr);
    return rc;
}