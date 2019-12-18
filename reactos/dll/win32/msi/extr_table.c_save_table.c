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
typedef  size_t UINT ;
struct TYPE_11__ {int type; } ;
struct TYPE_10__ {int /*<<< orphan*/  storage; } ;
struct TYPE_9__ {scalar_t__ persistent; size_t col_count; size_t row_count; int /*<<< orphan*/  name; int /*<<< orphan*/ ** data; TYPE_6__* colinfo; int /*<<< orphan*/ * data_persistent; } ;
typedef  TYPE_1__ MSITABLE ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t) ; 
 size_t ERROR_FUNCTION_FAILED ; 
 size_t ERROR_NOT_ENOUGH_MEMORY ; 
 size_t ERROR_SUCCESS ; 
 size_t LONG_STR_BYTES ; 
 scalar_t__ MSICONDITION_FALSE ; 
 int MSITYPE_STRING ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t bytes_per_column (TYPE_2__*,TYPE_6__*,size_t) ; 
 size_t debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msi_alloc_zero (size_t) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 size_t msi_table_get_row_size (TYPE_2__*,TYPE_6__*,size_t,size_t) ; 
 size_t read_table_int (int /*<<< orphan*/ **,size_t,size_t,size_t) ; 
 size_t write_stream_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT save_table( MSIDATABASE *db, const MSITABLE *t, UINT bytes_per_strref )
{
    BYTE *rawdata = NULL;
    UINT rawsize, i, j, row_size, row_count;
    UINT r = ERROR_FUNCTION_FAILED;

    /* Nothing to do for non-persistent tables */
    if( t->persistent == MSICONDITION_FALSE )
        return ERROR_SUCCESS;

    TRACE("Saving %s\n", debugstr_w( t->name ) );

    row_size = msi_table_get_row_size( db, t->colinfo, t->col_count, bytes_per_strref );
    row_count = t->row_count;
    for (i = 0; i < t->row_count; i++)
    {
        if (!t->data_persistent[i])
        {
            row_count = 1; /* yes, this is bizarre */
            break;
        }
    }
    rawsize = row_count * row_size;
    rawdata = msi_alloc_zero( rawsize );
    if( !rawdata )
    {
        r = ERROR_NOT_ENOUGH_MEMORY;
        goto err;
    }

    rawsize = 0;
    for (i = 0; i < row_count; i++)
    {
        UINT ofs = 0, ofs_mem = 0;

        if (!t->data_persistent[i]) break;

        for (j = 0; j < t->col_count; j++)
        {
            UINT m = bytes_per_column( db, &t->colinfo[j], LONG_STR_BYTES );
            UINT n = bytes_per_column( db, &t->colinfo[j], bytes_per_strref );
            UINT k;

            if (n != 2 && n != 3 && n != 4)
            {
                ERR("oops - unknown column width %d\n", n);
                goto err;
            }
            if (t->colinfo[j].type & MSITYPE_STRING && n < m)
            {
                UINT id = read_table_int( t->data, i, ofs_mem, LONG_STR_BYTES );
                if (id > 1 << bytes_per_strref * 8)
                {
                    ERR("string id %u out of range\n", id);
                    goto err;
                }
            }
            for (k = 0; k < n; k++)
            {
                rawdata[ofs * row_count + i * n + k] = t->data[i][ofs_mem + k];
            }
            ofs_mem += m;
            ofs += n;
        }
        rawsize += row_size;
    }

    TRACE("writing %d bytes\n", rawsize);
    r = write_stream_data( db->storage, t->name, rawdata, rawsize, TRUE );

err:
    msi_free( rawdata );
    return r;
}