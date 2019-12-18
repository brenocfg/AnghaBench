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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_14__ {int /*<<< orphan*/  persistent; int /*<<< orphan*/  Directory; } ;
struct TYPE_13__ {int /*<<< orphan*/  db; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_11__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  TYPE_3__ MSIPACKAGE ;
typedef  TYPE_4__ MSIFOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_2__**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_ViewExecute (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSI_ViewFetch (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT load_folder_persistence( MSIPACKAGE *package, MSIFOLDER *folder )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        '`','C','r','e','a','t','e','F','o','l','d','e','r','`',' ','W','H','E','R','E',' ',
        '`','D','i','r','e','c','t','o','r','y','_','`',' ','=','\'','%','s','\'',0};
    MSIQUERY *view;

    folder->persistent = FALSE;
    if (!MSI_OpenQuery( package->db, &view, query, folder->Directory ))
    {
        if (!MSI_ViewExecute( view, NULL ))
        {
            MSIRECORD *rec;
            if (!MSI_ViewFetch( view, &rec ))
            {
                TRACE("directory %s is persistent\n", debugstr_w(folder->Directory));
                folder->persistent = TRUE;
                msiobj_release( &rec->hdr );
            }
        }
        msiobj_release( &view->hdr );
    }
    return ERROR_SUCCESS;
}