#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_6__ {size_t num_cols; TYPE_1__* columns; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_2__ MSITABLEVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 size_t ERROR_OUTOFMEMORY ; 
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int MSITYPE_KEY ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * encode_streamname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/ * msi_dup_record_field (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * szDot ; 

__attribute__((used)) static UINT msi_record_encoded_stream_name( const MSITABLEVIEW *tv, MSIRECORD *rec, LPWSTR *pstname )
{
    LPWSTR stname = NULL, sval, p;
    DWORD len;
    UINT i, r;

    TRACE("%p %p\n", tv, rec);

    len = lstrlenW( tv->name ) + 1;
    stname = msi_alloc( len*sizeof(WCHAR) );
    if ( !stname )
    {
       r = ERROR_OUTOFMEMORY;
       goto err;
    }

    lstrcpyW( stname, tv->name );

    for ( i = 0; i < tv->num_cols; i++ )
    {
        if ( tv->columns[i].type & MSITYPE_KEY )
        {
            sval = msi_dup_record_field( rec, i + 1 );
            if ( !sval )
            {
                r = ERROR_OUTOFMEMORY;
                goto err;
            }

            len += lstrlenW( szDot ) + lstrlenW ( sval );
            p = msi_realloc ( stname, len*sizeof(WCHAR) );
            if ( !p )
            {
                r = ERROR_OUTOFMEMORY;
                msi_free(sval);
                goto err;
            }
            stname = p;

            lstrcatW( stname, szDot );
            lstrcatW( stname, sval );

            msi_free( sval );
        }
        else
            continue;
    }

    *pstname = encode_streamname( FALSE, stname );
    msi_free( stname );

    return ERROR_SUCCESS;

err:
    msi_free ( stname );
    *pstname = NULL;
    return r;
}