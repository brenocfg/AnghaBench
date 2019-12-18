#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  string_table ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
typedef  int UINT ;
struct TYPE_15__ {int type; } ;
struct TYPE_14__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_13__ {int num_cols; int /*<<< orphan*/  db; TYPE_3__* columns; } ;
typedef  TYPE_1__ MSITABLEVIEW ;
typedef  TYPE_2__ MSIRECORD ;
typedef  TYPE_3__ MSICOLUMNINFO ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int ERROR_SUCCESS ; 
 int IStorage_OpenStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ MSITYPE_IS_BINARY (int) ; 
 int MSITYPE_KEY ; 
 int MSITYPE_STRING ; 
 TYPE_2__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_RecordSetInteger (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  MSI_RecordSetStream (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int bytes_per_column (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int debugstr_w (int /*<<< orphan*/ ) ; 
 int debugstr_wn (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 int msi_record_encoded_stream_name (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_record_set_string (TYPE_2__*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * msi_string_lookup (int /*<<< orphan*/  const*,int,int*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int read_raw_int (int const*,int,int) ; 

__attribute__((used)) static MSIRECORD *msi_get_transform_record( const MSITABLEVIEW *tv, const string_table *st,
                                            IStorage *stg, const BYTE *rawdata, UINT bytes_per_strref )
{
    UINT i, val, ofs = 0;
    USHORT mask;
    MSICOLUMNINFO *columns = tv->columns;
    MSIRECORD *rec;

    mask = rawdata[0] | (rawdata[1] << 8);
    rawdata += 2;

    rec = MSI_CreateRecord( tv->num_cols );
    if( !rec )
        return rec;

    TRACE("row ->\n");
    for( i=0; i<tv->num_cols; i++ )
    {
        if ( (mask&1) && (i>=(mask>>8)) )
            break;
        /* all keys must be present */
        if ( (~mask&1) && (~columns[i].type & MSITYPE_KEY) && ((1<<i) & ~mask) )
            continue;

        if( MSITYPE_IS_BINARY(tv->columns[i].type) )
        {
            LPWSTR encname;
            IStream *stm = NULL;
            UINT r;

            ofs += bytes_per_column( tv->db, &columns[i], bytes_per_strref );

            r = msi_record_encoded_stream_name( tv, rec, &encname );
            if ( r != ERROR_SUCCESS )
            {
                msiobj_release( &rec->hdr );
                return NULL;
            }
            r = IStorage_OpenStream( stg, encname, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &stm );
            if ( r != ERROR_SUCCESS )
            {
                msiobj_release( &rec->hdr );
                msi_free( encname );
                return NULL;
            }

            MSI_RecordSetStream( rec, i+1, stm );
            TRACE(" field %d [%s]\n", i+1, debugstr_w(encname));
            msi_free( encname );
        }
        else if( columns[i].type & MSITYPE_STRING )
        {
            int len;
            const WCHAR *sval;

            val = read_raw_int(rawdata, ofs, bytes_per_strref);
            sval = msi_string_lookup( st, val, &len );
            msi_record_set_string( rec, i+1, sval, len );
            TRACE(" field %d [%s]\n", i+1, debugstr_wn(sval, len));
            ofs += bytes_per_strref;
        }
        else
        {
            UINT n = bytes_per_column( tv->db, &columns[i], bytes_per_strref );
            switch( n )
            {
            case 2:
                val = read_raw_int(rawdata, ofs, n);
                if (val)
                    MSI_RecordSetInteger( rec, i+1, val-0x8000 );
                TRACE(" field %d [0x%04x]\n", i+1, val );
                break;
            case 4:
                val = read_raw_int(rawdata, ofs, n);
                if (val)
                    MSI_RecordSetInteger( rec, i+1, val^0x80000000 );
                TRACE(" field %d [0x%08x]\n", i+1, val );
                break;
            default:
                ERR("oops - unknown column width %d\n", n);
                break;
            }
            ofs += n;
        }
    }
    return rec;
}