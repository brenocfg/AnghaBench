#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ uint16 ;
typedef  size_t tmsize_t ;
typedef  scalar_t__ int64 ;
typedef  scalar_t__ int32 ;
struct TYPE_10__ {scalar_t__ tif_diroff; int tif_flags; int /*<<< orphan*/  tif_name; int /*<<< orphan*/  tif_clientdata; } ;
typedef  scalar_t__ TIFFDataType ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  ReadOK (TYPE_1__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SeekOK (TYPE_1__*,scalar_t__) ; 
 size_t TIFFDataWidth (scalar_t__) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 int /*<<< orphan*/  TIFFFindField (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TIFFSeekFile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFSwabArrayOfLong (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  TIFFSwabArrayOfLong8 (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  TIFFSwabArrayOfShort (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  TIFFSwabLong (scalar_t__*) ; 
 int /*<<< orphan*/  TIFFSwabLong8 (scalar_t__*) ; 
 int /*<<< orphan*/  TIFFSwabShort (scalar_t__*) ; 
 int /*<<< orphan*/  TIFF_ANY ; 
 int TIFF_BIGTIFF ; 
 scalar_t__ TIFF_IFD ; 
 scalar_t__ TIFF_IFD8 ; 
 scalar_t__ TIFF_LONG ; 
 scalar_t__ TIFF_LONG8 ; 
 scalar_t__ TIFF_SLONG ; 
 scalar_t__ TIFF_SLONG8 ; 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  WriteOK (TYPE_1__*,scalar_t__*,size_t) ; 
 scalar_t__ _TIFFCheckMalloc (TYPE_1__*,size_t,size_t,char*) ; 
 int /*<<< orphan*/  _TIFFfree (scalar_t__*) ; 
 scalar_t__ isMapped (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

int
_TIFFRewriteField(TIFF* tif, uint16 tag, TIFFDataType in_datatype, 
                  tmsize_t count, void* data)
{
    static const char module[] = "TIFFResetField";
    /* const TIFFField* fip = NULL; */
    uint16 dircount;
    tmsize_t dirsize;
    uint8 direntry_raw[20];
    uint16 entry_tag = 0;
    uint16 entry_type = 0;
    uint64 entry_count = 0;
    uint64 entry_offset = 0;
    int    value_in_entry = 0;
    uint64 read_offset;
    uint8 *buf_to_write = NULL;
    TIFFDataType datatype;

/* -------------------------------------------------------------------- */
/*      Find field definition.                                          */
/* -------------------------------------------------------------------- */
    /*fip =*/ TIFFFindField(tif, tag, TIFF_ANY);

/* -------------------------------------------------------------------- */
/*      Do some checking this is a straight forward case.               */
/* -------------------------------------------------------------------- */
    if( isMapped(tif) )
    {
        TIFFErrorExt( tif->tif_clientdata, module, 
                      "Memory mapped files not currently supported for this operation." );
        return 0;
    }

    if( tif->tif_diroff == 0 )
    {
        TIFFErrorExt( tif->tif_clientdata, module, 
                      "Attempt to reset field on directory not already on disk." );
        return 0;
    }

/* -------------------------------------------------------------------- */
/*      Read the directory entry count.                                 */
/* -------------------------------------------------------------------- */
    if (!SeekOK(tif, tif->tif_diroff)) {
        TIFFErrorExt(tif->tif_clientdata, module,
                     "%s: Seek error accessing TIFF directory",
                     tif->tif_name);
        return 0;
    }

    read_offset = tif->tif_diroff;

    if (!(tif->tif_flags&TIFF_BIGTIFF))
    {
        if (!ReadOK(tif, &dircount, sizeof (uint16))) {
            TIFFErrorExt(tif->tif_clientdata, module,
                         "%s: Can not read TIFF directory count",
                         tif->tif_name);
            return 0;
        }
        if (tif->tif_flags & TIFF_SWAB)
            TIFFSwabShort(&dircount);
        dirsize = 12;
        read_offset += 2;
    } else {
        uint64 dircount64;
        if (!ReadOK(tif, &dircount64, sizeof (uint64))) {
            TIFFErrorExt(tif->tif_clientdata, module,
                         "%s: Can not read TIFF directory count",
                         tif->tif_name);
            return 0;
        }
        if (tif->tif_flags & TIFF_SWAB)
            TIFFSwabLong8(&dircount64);
        dircount = (uint16)dircount64;
        dirsize = 20;
        read_offset += 8;
    }

/* -------------------------------------------------------------------- */
/*      Read through directory to find target tag.                      */
/* -------------------------------------------------------------------- */
    while( dircount > 0 )
    {
        if (!ReadOK(tif, direntry_raw, dirsize)) {
            TIFFErrorExt(tif->tif_clientdata, module,
                         "%s: Can not read TIFF directory entry.",
                         tif->tif_name);
            return 0;
        }

        memcpy( &entry_tag, direntry_raw + 0, sizeof(uint16) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabShort( &entry_tag );

        if( entry_tag == tag )
            break;

        read_offset += dirsize;
    }

    if( entry_tag != tag )
    {
        TIFFErrorExt(tif->tif_clientdata, module,
                     "%s: Could not find tag %d.",
                     tif->tif_name, tag );
        return 0;
    }

/* -------------------------------------------------------------------- */
/*      Extract the type, count and offset for this entry.              */
/* -------------------------------------------------------------------- */
    memcpy( &entry_type, direntry_raw + 2, sizeof(uint16) );
    if (tif->tif_flags&TIFF_SWAB)
        TIFFSwabShort( &entry_type );

    if (!(tif->tif_flags&TIFF_BIGTIFF))
    {
        uint32 value;
        
        memcpy( &value, direntry_raw + 4, sizeof(uint32) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabLong( &value );
        entry_count = value;

        memcpy( &value, direntry_raw + 8, sizeof(uint32) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabLong( &value );
        entry_offset = value;
    }
    else
    {
        memcpy( &entry_count, direntry_raw + 4, sizeof(uint64) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabLong8( &entry_count );

        memcpy( &entry_offset, direntry_raw + 12, sizeof(uint64) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabLong8( &entry_offset );
    }

/* -------------------------------------------------------------------- */
/*      What data type do we want to write this as?                     */
/* -------------------------------------------------------------------- */
    if( TIFFDataWidth(in_datatype) == 8 && !(tif->tif_flags&TIFF_BIGTIFF) )
    {
        if( in_datatype == TIFF_LONG8 )
            datatype = TIFF_LONG;
        else if( in_datatype == TIFF_SLONG8 )
            datatype = TIFF_SLONG;
        else if( in_datatype == TIFF_IFD8 )
            datatype = TIFF_IFD;
        else
            datatype = in_datatype;
    }
    else 
        datatype = in_datatype;

/* -------------------------------------------------------------------- */
/*      Prepare buffer of actual data to write.  This includes          */
/*      swabbing as needed.                                             */
/* -------------------------------------------------------------------- */
    buf_to_write =
	    (uint8 *)_TIFFCheckMalloc(tif, count, TIFFDataWidth(datatype),
				      "for field buffer.");
    if (!buf_to_write)
        return 0;

    if( datatype == in_datatype )
        memcpy( buf_to_write, data, count * TIFFDataWidth(datatype) );
    else if( datatype == TIFF_SLONG && in_datatype == TIFF_SLONG8 )
    {
	tmsize_t i;

        for( i = 0; i < count; i++ )
        {
            ((int32 *) buf_to_write)[i] = 
                (int32) ((int64 *) data)[i];
            if( (int64) ((int32 *) buf_to_write)[i] != ((int64 *) data)[i] )
            {
                _TIFFfree( buf_to_write );
                TIFFErrorExt( tif->tif_clientdata, module, 
                              "Value exceeds 32bit range of output type." );
                return 0;
            }
        }
    }
    else if( (datatype == TIFF_LONG && in_datatype == TIFF_LONG8)
             || (datatype == TIFF_IFD && in_datatype == TIFF_IFD8) )
    {
	tmsize_t i;

        for( i = 0; i < count; i++ )
        {
            ((uint32 *) buf_to_write)[i] = 
                (uint32) ((uint64 *) data)[i];
            if( (uint64) ((uint32 *) buf_to_write)[i] != ((uint64 *) data)[i] )
            {
                _TIFFfree( buf_to_write );
                TIFFErrorExt( tif->tif_clientdata, module, 
                              "Value exceeds 32bit range of output type." );
                return 0;
            }
        }
    }

    if( TIFFDataWidth(datatype) > 1 && (tif->tif_flags&TIFF_SWAB) )
    {
        if( TIFFDataWidth(datatype) == 2 )
            TIFFSwabArrayOfShort( (uint16 *) buf_to_write, count );
        else if( TIFFDataWidth(datatype) == 4 )
            TIFFSwabArrayOfLong( (uint32 *) buf_to_write, count );
        else if( TIFFDataWidth(datatype) == 8 )
            TIFFSwabArrayOfLong8( (uint64 *) buf_to_write, count );
    }

/* -------------------------------------------------------------------- */
/*      Is this a value that fits into the directory entry?             */
/* -------------------------------------------------------------------- */
    if (!(tif->tif_flags&TIFF_BIGTIFF))
    {
        if( TIFFDataWidth(datatype) * count <= 4 )
        {
            entry_offset = read_offset + 8;
            value_in_entry = 1;
        }
    }
    else
    {
        if( TIFFDataWidth(datatype) * count <= 8 )
        {
            entry_offset = read_offset + 12;
            value_in_entry = 1;
        }
    }

/* -------------------------------------------------------------------- */
/*      If the tag type, and count match, then we just write it out     */
/*      over the old values without altering the directory entry at     */
/*      all.                                                            */
/* -------------------------------------------------------------------- */
    if( entry_count == (uint64)count && entry_type == (uint16) datatype )
    {
        if (!SeekOK(tif, entry_offset)) {
            _TIFFfree( buf_to_write );
            TIFFErrorExt(tif->tif_clientdata, module,
                         "%s: Seek error accessing TIFF directory",
                         tif->tif_name);
            return 0;
        }
        if (!WriteOK(tif, buf_to_write, count*TIFFDataWidth(datatype))) {
            _TIFFfree( buf_to_write );
            TIFFErrorExt(tif->tif_clientdata, module,
                         "Error writing directory link");
            return (0);
        }

        _TIFFfree( buf_to_write );
        return 1;
    }

/* -------------------------------------------------------------------- */
/*      Otherwise, we write the new tag data at the end of the file.    */
/* -------------------------------------------------------------------- */
    if( !value_in_entry )
    {
        entry_offset = TIFFSeekFile(tif,0,SEEK_END);
        
        if (!WriteOK(tif, buf_to_write, count*TIFFDataWidth(datatype))) {
            _TIFFfree( buf_to_write );
            TIFFErrorExt(tif->tif_clientdata, module,
                         "Error writing directory link");
            return (0);
        }
    }
    else
    {
        memcpy( &entry_offset, buf_to_write, count*TIFFDataWidth(datatype));
    }

    _TIFFfree( buf_to_write );
    buf_to_write = 0;

/* -------------------------------------------------------------------- */
/*      Adjust the directory entry.                                     */
/* -------------------------------------------------------------------- */
    entry_type = datatype;
    memcpy( direntry_raw + 2, &entry_type, sizeof(uint16) );
    if (tif->tif_flags&TIFF_SWAB)
        TIFFSwabShort( (uint16 *) (direntry_raw + 2) );

    if (!(tif->tif_flags&TIFF_BIGTIFF))
    {
        uint32 value;

        value = (uint32) entry_count;
        memcpy( direntry_raw + 4, &value, sizeof(uint32) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabLong( (uint32 *) (direntry_raw + 4) );

        value = (uint32) entry_offset;
        memcpy( direntry_raw + 8, &value, sizeof(uint32) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabLong( (uint32 *) (direntry_raw + 8) );
    }
    else
    {
        memcpy( direntry_raw + 4, &entry_count, sizeof(uint64) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabLong8( (uint64 *) (direntry_raw + 4) );

        memcpy( direntry_raw + 12, &entry_offset, sizeof(uint64) );
        if (tif->tif_flags&TIFF_SWAB)
            TIFFSwabLong8( (uint64 *) (direntry_raw + 12) );
    }

/* -------------------------------------------------------------------- */
/*      Write the directory entry out to disk.                          */
/* -------------------------------------------------------------------- */
    if (!SeekOK(tif, read_offset )) {
        TIFFErrorExt(tif->tif_clientdata, module,
                     "%s: Seek error accessing TIFF directory",
                     tif->tif_name);
        return 0;
    }

    if (!WriteOK(tif, direntry_raw,dirsize))
    {
        TIFFErrorExt(tif->tif_clientdata, module,
                     "%s: Can not write TIFF directory entry.",
                     tif->tif_name);
        return 0;
    }
    
    return 1;
}