#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  db; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_11__ {scalar_t__ MinVersionMS; scalar_t__ MinVersionLS; scalar_t__ MaxVersionMS; scalar_t__ MaxVersionLS; scalar_t__ MinSize; scalar_t__ MaxSize; void* Languages; void* File; int /*<<< orphan*/  MaxTime; int /*<<< orphan*/  MinTime; void* Name; } ;
typedef  TYPE_1__ MSISIGNATURE ;
typedef  TYPE_2__ MSIRECORD ;
typedef  TYPE_3__ MSIPACKAGE ;
typedef  void* LPWSTR ;
typedef  void* LPCWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DosDateTimeToFileTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HIWORD (scalar_t__) ; 
 int /*<<< orphan*/  LOWORD (scalar_t__) ; 
 scalar_t__ MSI_NULL_INTEGER ; 
 TYPE_2__* MSI_QueryGetRecord (int /*<<< orphan*/ ,char const*,void*) ; 
 scalar_t__ MSI_RecordGetInteger (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,...) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* msi_dup_record_field (TYPE_2__*,int) ; 
 int /*<<< orphan*/  msi_free (void*) ; 
 int /*<<< orphan*/  msi_parse_version_string (void*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 void* strchrW (void*,char) ; 
 int strlenW (void*) ; 

__attribute__((used)) static UINT ACTION_AppSearchGetSignature(MSIPACKAGE *package, MSISIGNATURE *sig, LPCWSTR name)
{
    static const WCHAR query[] = {
        's','e','l','e','c','t',' ','*',' ',
        'f','r','o','m',' ',
        'S','i','g','n','a','t','u','r','e',' ',
        'w','h','e','r','e',' ','S','i','g','n','a','t','u','r','e',' ','=',' ',
        '\'','%','s','\'',0};
    LPWSTR minVersion, maxVersion, p;
    MSIRECORD *row;
    DWORD time;

    TRACE("package %p, sig %p\n", package, sig);

    memset(sig, 0, sizeof(*sig));
    sig->Name = name;
    row = MSI_QueryGetRecord( package->db, query, name );
    if (!row)
    {
        TRACE("failed to query signature for %s\n", debugstr_w(name));
        return ERROR_SUCCESS;
    }

    /* get properties */
    sig->File = msi_dup_record_field(row,2);
    if ((p = strchrW(sig->File, '|')))
    {
        p++;
        memmove(sig->File, p, (strlenW(p) + 1) * sizeof(WCHAR));
    }

    minVersion = msi_dup_record_field(row,3);
    if (minVersion)
    {
        msi_parse_version_string( minVersion, &sig->MinVersionMS, &sig->MinVersionLS );
        msi_free( minVersion );
    }
    maxVersion = msi_dup_record_field(row,4);
    if (maxVersion)
    {
        msi_parse_version_string( maxVersion, &sig->MaxVersionMS, &sig->MaxVersionLS );
        msi_free( maxVersion );
    }
    sig->MinSize = MSI_RecordGetInteger(row,5);
    if (sig->MinSize == MSI_NULL_INTEGER)
        sig->MinSize = 0;
    sig->MaxSize = MSI_RecordGetInteger(row,6);
    if (sig->MaxSize == MSI_NULL_INTEGER)
        sig->MaxSize = 0;
    sig->Languages = msi_dup_record_field(row,9);
    time = MSI_RecordGetInteger(row,7);
    if (time != MSI_NULL_INTEGER)
        DosDateTimeToFileTime(HIWORD(time), LOWORD(time), &sig->MinTime);
    time = MSI_RecordGetInteger(row,8);
    if (time != MSI_NULL_INTEGER)
        DosDateTimeToFileTime(HIWORD(time), LOWORD(time), &sig->MaxTime);

    TRACE("Found file name %s for Signature_ %s;\n",
          debugstr_w(sig->File), debugstr_w(name));
    TRACE("MinVersion is %d.%d.%d.%d\n", HIWORD(sig->MinVersionMS),
          LOWORD(sig->MinVersionMS), HIWORD(sig->MinVersionLS),
          LOWORD(sig->MinVersionLS));
    TRACE("MaxVersion is %d.%d.%d.%d\n", HIWORD(sig->MaxVersionMS),
          LOWORD(sig->MaxVersionMS), HIWORD(sig->MaxVersionLS),
          LOWORD(sig->MaxVersionLS));
    TRACE("MinSize is %d, MaxSize is %d;\n", sig->MinSize, sig->MaxSize);
    TRACE("Languages is %s\n", debugstr_w(sig->Languages));

    msiobj_release( &row->hdr );

    return ERROR_SUCCESS;
}