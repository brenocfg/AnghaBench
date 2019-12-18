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
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
struct TYPE_7__ {int /*<<< orphan*/  hdr; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIQUERY ;
typedef  TYPE_2__ MSIPACKAGE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_1__**,char const*,char const*) ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 scalar_t__ MSI_ViewExecute (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ MSI_ViewFetch (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MSIRECORD *get_assembly_record( MSIPACKAGE *package, const WCHAR *comp )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
         '`','M','s','i','A','s','s','e','m','b','l','y','`',' ',
         'W','H','E','R','E',' ','`','C','o','m','p','o','n','e','n','t','_','`',
         ' ','=',' ','\'','%','s','\'',0};
    MSIQUERY *view;
    MSIRECORD *rec;
    UINT r;

    r = MSI_OpenQuery( package->db, &view, query, comp );
    if (r != ERROR_SUCCESS)
        return NULL;

    r = MSI_ViewExecute( view, NULL );
    if (r != ERROR_SUCCESS)
    {
        msiobj_release( &view->hdr );
        return NULL;
    }
    r = MSI_ViewFetch( view, &rec );
    if (r != ERROR_SUCCESS)
    {
        msiobj_release( &view->hdr );
        return NULL;
    }
    if (!MSI_RecordGetString( rec, 4 ))
        TRACE("component is a global assembly\n");

    msiobj_release( &view->hdr );
    return rec;
}