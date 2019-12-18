#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  scalar_t__* LPWSTR ;
typedef  int* LPDWORD ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 TYPE_1__* MSI_CloneRecord (TYPE_1__*) ; 
 int MSI_RecordGetFieldCount (TYPE_1__*) ; 
 int /*<<< orphan*/ * MSI_RecordGetString (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*,int*) ; 
 int /*<<< orphan*/ * build_default_format (TYPE_1__*) ; 
 int /*<<< orphan*/  deformat_string_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  dump_record (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * msi_dup_record_field (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

UINT MSI_FormatRecordW( MSIPACKAGE* package, MSIRECORD* record, LPWSTR buffer,
                        LPDWORD size )
{
    WCHAR *format, *deformated = NULL;
    UINT rc = ERROR_INVALID_PARAMETER;
    DWORD len;
    MSIRECORD *record_deformated;
    int field_count, i;

    TRACE("%p %p %p %p\n", package, record, buffer, size);
    dump_record(record);

    if (!(format = msi_dup_record_field( record, 0 )))
        format = build_default_format( record );

    field_count = MSI_RecordGetFieldCount(record);
    record_deformated = MSI_CloneRecord(record);
    if (!record_deformated)
    {
        rc = ERROR_OUTOFMEMORY;
        goto end;
    }
    MSI_RecordSetStringW(record_deformated, 0, format);
    for (i = 1; i <= field_count; i++)
    {
        if (MSI_RecordGetString(record, i))
        {
            deformat_string_internal(package, MSI_RecordGetString(record, i), &deformated, &len, NULL);
            MSI_RecordSetStringW(record_deformated, i, deformated);
            msi_free(deformated);
        }
    }

    deformat_string_internal(package, format, &deformated, &len, record_deformated);
    if (buffer)
    {
        if (*size>len)
        {
            memcpy(buffer,deformated,len*sizeof(WCHAR));
            rc = ERROR_SUCCESS;
            buffer[len] = 0;
        }
        else
        {
            if (*size > 0)
            {
                memcpy(buffer,deformated,(*size)*sizeof(WCHAR));
                buffer[(*size)-1] = 0;
            }
            rc = ERROR_MORE_DATA;
        }
    }
    else rc = ERROR_SUCCESS;

    *size = len;
    msiobj_release(&record_deformated->hdr);
end:
    msi_free( format );
    msi_free( deformated );
    return rc;
}