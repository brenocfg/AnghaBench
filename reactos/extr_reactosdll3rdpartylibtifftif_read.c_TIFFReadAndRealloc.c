#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_4__ {scalar_t__ tif_rawdatasize; int tif_flags; scalar_t__ tif_rawdata; scalar_t__ tif_col; scalar_t__ tif_row; int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 scalar_t__ TIFFReadFile (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int TIFF_MYBUFFER ; 
 scalar_t__ TIFFroundup_64 (scalar_t__,int) ; 
 int /*<<< orphan*/  _TIFFfree (int /*<<< orphan*/ *) ; 
 scalar_t__ _TIFFrealloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int TIFFReadAndRealloc( TIFF* tif, tmsize_t size,
                               tmsize_t rawdata_offset,
                               int is_strip, uint32 strip_or_tile,
                               const char* module )
{
#if SIZEOF_SIZE_T == 8
        tmsize_t threshold = INITIAL_THRESHOLD;
#endif
        tmsize_t already_read = 0;

        /* On 64 bit processes, read first a maximum of 1 MB, then 10 MB, etc */
        /* so as to avoid allocating too much memory in case the file is too */
        /* short. We could ask for the file size, but this might be */
        /* expensive with some I/O layers (think of reading a gzipped file) */
        /* Restrict to 64 bit processes, so as to avoid reallocs() */
        /* on 32 bit processes where virtual memory is scarce.  */
        while( already_read < size )
        {
            tmsize_t bytes_read;
            tmsize_t to_read = size - already_read;
#if SIZEOF_SIZE_T == 8
            if( to_read >= threshold && threshold < MAX_THRESHOLD &&
                already_read + to_read + rawdata_offset > tif->tif_rawdatasize )
            {
                to_read = threshold;
                threshold *= THRESHOLD_MULTIPLIER;
            }
#endif
            if (already_read + to_read + rawdata_offset > tif->tif_rawdatasize) {
                uint8* new_rawdata;
                assert((tif->tif_flags & TIFF_MYBUFFER) != 0);
                tif->tif_rawdatasize = (tmsize_t)TIFFroundup_64(
                        (uint64)already_read + to_read + rawdata_offset, 1024);
                if (tif->tif_rawdatasize==0) {
                    TIFFErrorExt(tif->tif_clientdata, module,
                                "Invalid buffer size");
                    return 0;
                }
                new_rawdata = (uint8*) _TIFFrealloc(
                                tif->tif_rawdata, tif->tif_rawdatasize);
                if( new_rawdata == 0 )
                {
                    TIFFErrorExt(tif->tif_clientdata, module,
                        "No space for data buffer at scanline %lu",
                        (unsigned long) tif->tif_row);
                    _TIFFfree(tif->tif_rawdata);
                    tif->tif_rawdata = 0;
                    tif->tif_rawdatasize = 0;
                    return 0;
                }
                tif->tif_rawdata = new_rawdata;
            }

            bytes_read = TIFFReadFile(tif,
                tif->tif_rawdata + rawdata_offset + already_read, to_read);
            already_read += bytes_read;
            if (bytes_read != to_read) {
                memset( tif->tif_rawdata + rawdata_offset + already_read, 0,
                        tif->tif_rawdatasize - rawdata_offset - already_read );
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
                if( is_strip )
                {
                    TIFFErrorExt(tif->tif_clientdata, module,
                        "Read error at scanline %lu; got %I64u bytes, "
                        "expected %I64u",
                                        (unsigned long) tif->tif_row,
                                        (unsigned __int64) already_read,
                                        (unsigned __int64) size);
                }
                else
                {
                    TIFFErrorExt(tif->tif_clientdata, module,
                        "Read error at row %lu, col %lu, tile %lu; "
                        "got %I64u bytes, expected %I64u",
                                        (unsigned long) tif->tif_row,
                                        (unsigned long) tif->tif_col,
                                        (unsigned long) strip_or_tile,
                                        (unsigned __int64) already_read,
                                        (unsigned __int64) size);
                }
#else
                if( is_strip )
                {
                    TIFFErrorExt(tif->tif_clientdata, module,
                        "Read error at scanline %lu; got %llu bytes, "
                        "expected %llu",
                                        (unsigned long) tif->tif_row,
                                        (unsigned long long) already_read,
                                        (unsigned long long) size);
                }
                else
                {
                    TIFFErrorExt(tif->tif_clientdata, module,
                        "Read error at row %lu, col %lu, tile %lu; "
                        "got %llu bytes, expected %llu",
                                        (unsigned long) tif->tif_row,
                                        (unsigned long) tif->tif_col,
                                        (unsigned long) strip_or_tile,
                                        (unsigned long long) already_read,
                                        (unsigned long long) size);
                }
#endif
                return 0;
            }
        }
        return 1;
}