#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  string_table ;
typedef  int USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int DWORD ;
typedef  int CHAR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int CP_ACP ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int ERROR_SUCCESS ; 
 int LONG_STR_BYTES ; 
 int /*<<< orphan*/  StringPersistent ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int add_string (int /*<<< orphan*/ *,int,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * init_stringtable (int,int) ; 
 int /*<<< orphan*/  msi_free (int*) ; 
 int read_stream_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  szStringData ; 
 int /*<<< orphan*/  szStringPool ; 

string_table *msi_load_string_table( IStorage *stg, UINT *bytes_per_strref )
{
    string_table *st = NULL;
    CHAR *data = NULL;
    USHORT *pool = NULL;
    UINT r, datasize = 0, poolsize = 0, codepage;
    DWORD i, count, offset, len, n, refs;

    r = read_stream_data( stg, szStringPool, TRUE, (BYTE **)&pool, &poolsize );
    if( r != ERROR_SUCCESS)
        goto end;
    r = read_stream_data( stg, szStringData, TRUE, (BYTE **)&data, &datasize );
    if( r != ERROR_SUCCESS)
        goto end;

    if ( (poolsize > 4) && (pool[1] & 0x8000) )
        *bytes_per_strref = LONG_STR_BYTES;
    else
        *bytes_per_strref = sizeof(USHORT);

    count = poolsize/4;
    if( poolsize > 4 )
        codepage = pool[0] | ( (pool[1] & ~0x8000) << 16 );
    else
        codepage = CP_ACP;
    st = init_stringtable( count, codepage );
    if (!st)
        goto end;

    offset = 0;
    n = 1;
    i = 1;
    while( i<count )
    {
        /* the string reference count is always the second word */
        refs = pool[i*2+1];

        /* empty entries have two zeros, still have a string id */
        if (pool[i*2] == 0 && refs == 0)
        {
            i++;
            n++;
            continue;
        }

        /*
         * If a string is over 64k, the previous string entry is made null
         * and its the high word of the length is inserted in the null string's
         * reference count field.
         */
        if( pool[i*2] == 0)
        {
            len = (pool[i*2+3] << 16) + pool[i*2+2];
            i += 2;
        }
        else
        {
            len = pool[i*2];
            i += 1;
        }

        if ( (offset + len) > datasize )
        {
            ERR("string table corrupt?\n");
            break;
        }

        r = add_string( st, n, data+offset, len, refs, StringPersistent );
        if( r != n )
            ERR("Failed to add string %d\n", n );
        n++;
        offset += len;
    }

    if ( datasize != offset )
        ERR("string table load failed! (%08x != %08x), please report\n", datasize, offset );

    TRACE("Loaded %d strings\n", count);

end:
    msi_free( pool );
    msi_free( data );

    return st;
}