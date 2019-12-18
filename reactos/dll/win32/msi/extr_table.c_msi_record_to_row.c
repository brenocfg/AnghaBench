#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_7__ {int num_cols; TYPE_2__* columns; TYPE_1__* db; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_5__ {int /*<<< orphan*/  strings; } ;
typedef  TYPE_3__ MSITABLEVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSITYPE_IS_BINARY (int) ; 
 int MSITYPE_KEY ; 
 int MSITYPE_STRING ; 
 size_t MSI_NULL_INTEGER ; 
 size_t MSI_RecordGetInteger (int /*<<< orphan*/ *,size_t) ; 
 size_t* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (size_t*) ; 
 int /*<<< orphan*/ * msi_record_get_string (int /*<<< orphan*/ *,size_t,int*) ; 
 size_t msi_string2id (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,size_t*) ; 

__attribute__((used)) static UINT* msi_record_to_row( const MSITABLEVIEW *tv, MSIRECORD *rec )
{
    UINT i, r, *data;

    data = msi_alloc( tv->num_cols *sizeof (UINT) );
    for( i=0; i<tv->num_cols; i++ )
    {
        data[i] = 0;

        if ( ~tv->columns[i].type & MSITYPE_KEY )
            continue;

        /* turn the transform column value into a row value */
        if ( ( tv->columns[i].type & MSITYPE_STRING ) &&
             ! MSITYPE_IS_BINARY(tv->columns[i].type) )
        {
            int len;
            const WCHAR *str = msi_record_get_string( rec, i+1, &len );
            if (str)
            {
                r = msi_string2id( tv->db->strings, str, len, &data[i] );

                /* if there's no matching string in the string table,
                   these keys can't match any record, so fail now. */
                if (r != ERROR_SUCCESS)
                {
                    msi_free( data );
                    return NULL;
                }
            }
            else data[i] = 0;
        }
        else
        {
            data[i] = MSI_RecordGetInteger( rec, i+1 );

            if (data[i] == MSI_NULL_INTEGER)
                data[i] = 0;
            else if ((tv->columns[i].type&0xff) == 2)
                data[i] += 0x8000;
            else
                data[i] += 0x80000000;
        }
    }
    return data;
}