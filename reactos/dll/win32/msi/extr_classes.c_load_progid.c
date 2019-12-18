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
typedef  char WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  progids; } ;
struct TYPE_10__ {struct TYPE_10__* VersionInd; struct TYPE_10__* CurVer; struct TYPE_10__* Parent; void* IconPath; void* Description; int /*<<< orphan*/ * Class; void* ProgID; int /*<<< orphan*/  entry; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPROGID ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  void* LPWSTR ;
typedef  void* LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 void* MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSI_RecordIsNull (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_given_class (TYPE_2__*,void*) ; 
 TYPE_1__* load_given_progid (TYPE_2__*,void*) ; 
 void* msi_alloc (int) ; 
 TYPE_1__* msi_alloc_zero (int) ; 
 void* msi_build_icon_path (TYPE_2__*,void*) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_free (void*) ; 
 int /*<<< orphan*/  sprintfW (void*,char const*,void*,int /*<<< orphan*/ ) ; 
 int strlenW (void*) ; 

__attribute__((used)) static MSIPROGID *load_progid( MSIPACKAGE* package, MSIRECORD *row )
{
    MSIPROGID *progid;
    LPCWSTR buffer;

    /* fill in the data */

    progid = msi_alloc_zero( sizeof(MSIPROGID) );
    if (!progid)
        return NULL;

    list_add_tail( &package->progids, &progid->entry );

    progid->ProgID = msi_dup_record_field(row,1);
    TRACE("loading progid %s\n",debugstr_w(progid->ProgID));

    buffer = MSI_RecordGetString(row,2);
    progid->Parent = load_given_progid(package,buffer);
    if (progid->Parent == NULL && buffer)
        FIXME("Unknown parent ProgID %s\n",debugstr_w(buffer));

    buffer = MSI_RecordGetString(row,3);
    progid->Class = load_given_class(package,buffer);
    if (progid->Class == NULL && buffer)
        FIXME("Unknown class %s\n",debugstr_w(buffer));

    progid->Description = msi_dup_record_field(row,4);

    if (!MSI_RecordIsNull(row,6))
    {
        INT icon_index = MSI_RecordGetInteger(row,6); 
        LPCWSTR FileName = MSI_RecordGetString(row,5);
        LPWSTR FilePath;
        static const WCHAR fmt[] = {'%','s',',','%','i',0};

        FilePath = msi_build_icon_path(package, FileName);
       
        progid->IconPath = msi_alloc( (strlenW(FilePath)+10)* sizeof(WCHAR) );

        sprintfW(progid->IconPath,fmt,FilePath,icon_index);

        msi_free(FilePath);
    }
    else
    {
        buffer = MSI_RecordGetString(row,5);
        if (buffer)
            progid->IconPath = msi_build_icon_path(package, buffer);
    }

    progid->CurVer = NULL;
    progid->VersionInd = NULL;

    /* if we have a parent then we may be that parents CurVer */
    if (progid->Parent && progid->Parent != progid)
    {
        MSIPROGID *parent = progid->Parent;

        while (parent->Parent && parent->Parent != parent)
            parent = parent->Parent;

        /* FIXME: need to determine if we are really the CurVer */

        progid->CurVer = parent;
        parent->VersionInd = progid;
    }
    
    return progid;
}