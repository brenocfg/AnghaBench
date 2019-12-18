#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_21__ {scalar_t__ Action; } ;
struct TYPE_20__ {int /*<<< orphan*/  db; } ;
struct TYPE_19__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  TYPE_3__ MSICOMPONENT ;
typedef  char* LPWSTR ;
typedef  TYPE_2__* LPVOID ;
typedef  char* LPCWSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ GetFileAttributesW (char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INSTALLMESSAGE_ACTIONDATA ; 
 scalar_t__ INSTALLSTATE_LOCAL ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_ProcessMessage (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int MSI_RecordGetInteger (TYPE_1__*,int) ; 
 char* MSI_RecordGetString (TYPE_1__*,int) ; 
 scalar_t__ MSI_RecordIsNull (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetInteger (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lstrcatW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  move_files_wildcard (char*,char*,int) ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_create_full_path (char*) ; 
 char* msi_dup_property (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 scalar_t__ msi_get_component_action (TYPE_2__*,TYPE_3__*) ; 
 TYPE_3__* msi_get_loaded_component (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msi_move_file (char*,char*,int) ; 
 int /*<<< orphan*/  msi_reduce_to_long_filename (char*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 scalar_t__ strchrW (char*,char) ; 
 char* strdupW (char*) ; 
 char* strrchrW (char*,char) ; 
 char* szBackSlash ; 

__attribute__((used)) static UINT ITERATE_MoveFiles( MSIRECORD *rec, LPVOID param )
{
    MSIPACKAGE *package = param;
    MSIRECORD *uirow;
    MSICOMPONENT *comp;
    LPCWSTR sourcename, component;
    LPWSTR sourcedir, destname = NULL, destdir = NULL, source = NULL, dest = NULL;
    int options;
    DWORD size;
    BOOL wildcards;

    component = MSI_RecordGetString(rec, 2);
    comp = msi_get_loaded_component(package, component);
    if (!comp)
        return ERROR_SUCCESS;

    comp->Action = msi_get_component_action( package, comp );
    if (comp->Action != INSTALLSTATE_LOCAL)
    {
        TRACE("component not scheduled for installation %s\n", debugstr_w(component));
        return ERROR_SUCCESS;
    }

    sourcename = MSI_RecordGetString(rec, 3);
    options = MSI_RecordGetInteger(rec, 7);

    sourcedir = msi_dup_property(package->db, MSI_RecordGetString(rec, 5));
    if (!sourcedir)
        goto done;

    destdir = msi_dup_property(package->db, MSI_RecordGetString(rec, 6));
    if (!destdir)
        goto done;

    if (!sourcename)
    {
        if (GetFileAttributesW(sourcedir) == INVALID_FILE_ATTRIBUTES)
            goto done;

        source = strdupW(sourcedir);
        if (!source)
            goto done;
    }
    else
    {
        size = lstrlenW(sourcedir) + lstrlenW(sourcename) + 2;
        source = msi_alloc(size * sizeof(WCHAR));
        if (!source)
            goto done;

        lstrcpyW(source, sourcedir);
        if (source[lstrlenW(source) - 1] != '\\')
            lstrcatW(source, szBackSlash);
        lstrcatW(source, sourcename);
    }

    wildcards = strchrW(source, '*') || strchrW(source, '?');

    if (MSI_RecordIsNull(rec, 4))
    {
        if (!wildcards)
        {
            WCHAR *p;
            if (sourcename)
                destname = strdupW(sourcename);
            else if ((p = strrchrW(sourcedir, '\\')))
                destname = strdupW(p + 1);
            else
                destname = strdupW(sourcedir);
            if (!destname)
                goto done;
        }
    }
    else
    {
        destname = strdupW(MSI_RecordGetString(rec, 4));
        if (destname) msi_reduce_to_long_filename(destname);
    }

    size = 0;
    if (destname)
        size = lstrlenW(destname);

    size += lstrlenW(destdir) + 2;
    dest = msi_alloc(size * sizeof(WCHAR));
    if (!dest)
        goto done;

    lstrcpyW(dest, destdir);
    if (dest[lstrlenW(dest) - 1] != '\\')
        lstrcatW(dest, szBackSlash);

    if (destname)
        lstrcatW(dest, destname);

    if (GetFileAttributesW(destdir) == INVALID_FILE_ATTRIBUTES)
    {
        if (!msi_create_full_path(destdir))
        {
            WARN("failed to create directory %u\n", GetLastError());
            goto done;
        }
    }

    if (!wildcards)
        msi_move_file(source, dest, options);
    else
        move_files_wildcard(source, dest, options);

done:
    uirow = MSI_CreateRecord( 9 );
    MSI_RecordSetStringW( uirow, 1, MSI_RecordGetString(rec, 1) );
    MSI_RecordSetInteger( uirow, 6, 1 ); /* FIXME */
    MSI_RecordSetStringW( uirow, 9, destdir );
    MSI_ProcessMessage(package, INSTALLMESSAGE_ACTIONDATA, uirow);
    msiobj_release( &uirow->hdr );

    msi_free(sourcedir);
    msi_free(destdir);
    msi_free(destname);
    msi_free(source);
    msi_free(dest);

    return ERROR_SUCCESS;
}