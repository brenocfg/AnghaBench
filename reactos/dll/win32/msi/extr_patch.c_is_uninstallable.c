#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ MSI_DatabaseOpenViewW (int /*<<< orphan*/ *,char const*,TYPE_2__**) ; 
 char* MSI_RecordGetString (TYPE_1__*,int) ; 
 scalar_t__ MSI_ViewExecute (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MSI_ViewFetch (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  atoiW (char const*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD is_uninstallable( MSIDATABASE *db )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','`','V','a','l','u','e','`',' ','F','R','O','M',' ',
        '`','M','s','i','P','a','t','c','h','M','e','t','a','d','a','t','a','`',' ',
        'W','H','E','R','E',' ','`','C','o','m','p','a','n','y','`',' ','I','S',' ',
        'N','U','L','L',' ','A','N','D',' ','`','P','r','o','p','e','r','t','y','`','=',
        '\'','A','l','l','o','w','R','e','m','o','v','a','l','\'',0};
    MSIQUERY *view;
    MSIRECORD *rec;
    DWORD ret = 0;

    if (MSI_DatabaseOpenViewW( db, query, &view ) != ERROR_SUCCESS) return 0;
    if (MSI_ViewExecute( view, 0 ) != ERROR_SUCCESS)
    {
        msiobj_release( &view->hdr );
        return 0;
    }

    if (MSI_ViewFetch( view, &rec ) == ERROR_SUCCESS)
    {
        const WCHAR *value = MSI_RecordGetString( rec, 1 );
        ret = atoiW( value );
        msiobj_release( &rec->hdr );
    }

    FIXME( "check other criteria\n" );

    msiobj_release( &view->hdr );
    return ret;
}