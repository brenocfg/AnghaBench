#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;
struct TYPE_11__ {int type; } ;
struct TYPE_10__ {int /*<<< orphan*/  bytes_per_strref; } ;
struct TYPE_9__ {int col_count; int row_count; void*** data; TYPE_6__* colinfo; int /*<<< orphan*/ * data_persistent; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ MSITABLE ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  void* BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  LONG_STR_BYTES ; 
 int MSITYPE_STRING ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int,int) ; 
 int bytes_per_column (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int debugstr_w (int /*<<< orphan*/ ) ; 
 void** msi_alloc (int) ; 
 void* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (void**) ; 
 int msi_table_get_row_size (TYPE_2__*,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_stream_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void***,int*) ; 

__attribute__((used)) static UINT read_table_from_storage( MSIDATABASE *db, MSITABLE *t, IStorage *stg )
{
    BYTE *rawdata = NULL;
    UINT rawsize = 0, i, j, row_size, row_size_mem;

    TRACE("%s\n",debugstr_w(t->name));

    row_size = msi_table_get_row_size( db, t->colinfo, t->col_count, db->bytes_per_strref );
    row_size_mem = msi_table_get_row_size( db, t->colinfo, t->col_count, LONG_STR_BYTES );

    /* if we can't read the table, just assume that it's empty */
    read_stream_data( stg, t->name, TRUE, &rawdata, &rawsize );
    if( !rawdata )
        return ERROR_SUCCESS;

    TRACE("Read %d bytes\n", rawsize );

    if( rawsize % row_size )
    {
        WARN("Table size is invalid %d/%d\n", rawsize, row_size );
        goto err;
    }

    if ((t->row_count = rawsize / row_size))
    {
        if (!(t->data = msi_alloc_zero( t->row_count * sizeof(USHORT *) ))) goto err;
        if (!(t->data_persistent = msi_alloc_zero( t->row_count * sizeof(BOOL) ))) goto err;
    }

    /* transpose all the data */
    TRACE("Transposing data from %d rows\n", t->row_count );
    for (i = 0; i < t->row_count; i++)
    {
        UINT ofs = 0, ofs_mem = 0;

        t->data[i] = msi_alloc( row_size_mem );
        if( !t->data[i] )
            goto err;
        t->data_persistent[i] = TRUE;

        for (j = 0; j < t->col_count; j++)
        {
            UINT m = bytes_per_column( db, &t->colinfo[j], LONG_STR_BYTES );
            UINT n = bytes_per_column( db, &t->colinfo[j], db->bytes_per_strref );
            UINT k;

            if ( n != 2 && n != 3 && n != 4 )
            {
                ERR("oops - unknown column width %d\n", n);
                goto err;
            }
            if (t->colinfo[j].type & MSITYPE_STRING && n < m)
            {
                for (k = 0; k < m; k++)
                {
                    if (k < n)
                        t->data[i][ofs_mem + k] = rawdata[ofs * t->row_count + i * n + k];
                    else
                        t->data[i][ofs_mem + k] = 0;
                }
            }
            else
            {
                for (k = 0; k < n; k++)
                    t->data[i][ofs_mem + k] = rawdata[ofs * t->row_count + i * n + k];
            }
            ofs_mem += m;
            ofs += n;
        }
    }

    msi_free( rawdata );
    return ERROR_SUCCESS;
err:
    msi_free( rawdata );
    return ERROR_FUNCTION_FAILED;
}