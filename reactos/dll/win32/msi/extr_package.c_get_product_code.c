#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  int /*<<< orphan*/  MSIDATABASE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_DatabaseOpenViewW (int /*<<< orphan*/ *,char const*,TYPE_2__**) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_ViewClose (TYPE_2__*) ; 
 scalar_t__ MSI_ViewExecute (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MSI_ViewFetch (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 char* strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *get_product_code( MSIDATABASE *db )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','`','V','a','l','u','e','`',' ',
        'F','R','O','M',' ','`','P','r','o','p','e','r','t','y','`',' ',
        'W','H','E','R','E',' ','`','P','r','o','p','e','r','t','y','`','=',
        '\'','P','r','o','d','u','c','t','C','o','d','e','\'',0};
    MSIQUERY *view;
    MSIRECORD *rec;
    WCHAR *ret = NULL;

    if (MSI_DatabaseOpenViewW( db, query, &view ) != ERROR_SUCCESS)
    {
        return NULL;
    }
    if (MSI_ViewExecute( view, 0 ) != ERROR_SUCCESS)
    {
        MSI_ViewClose( view );
        msiobj_release( &view->hdr );
        return NULL;
    }
    if (MSI_ViewFetch( view, &rec ) == ERROR_SUCCESS)
    {
        ret = strdupW( MSI_RecordGetString( rec, 1 ) );
        msiobj_release( &rec->hdr );
    }
    MSI_ViewClose( view );
    msiobj_release( &view->hdr );
    return ret;
}