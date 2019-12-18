#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_9__ {scalar_t__ (* tif_decodestrip ) (TYPE_1__*,void*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* tif_postdecode ) (TYPE_1__*,void*,scalar_t__) ;int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TIFFFileName (TYPE_1__*) ; 
 int /*<<< orphan*/  TIFFFillStrip (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TIFFReadEncodedStrip (TYPE_1__*,int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ TIFFReadEncodedStripGetStripSize (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* _TIFFmalloc (scalar_t__) ; 
 int /*<<< orphan*/  _TIFFmemset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_1__*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,void*,scalar_t__) ; 

tmsize_t
_TIFFReadEncodedStripAndAllocBuffer(TIFF* tif, uint32 strip,
                                    void **buf, tmsize_t bufsizetoalloc,
                                    tmsize_t size_to_read)
{
    tmsize_t this_stripsize;
    uint16 plane;

    if( *buf != NULL )
    {
        return TIFFReadEncodedStrip(tif, strip, *buf, size_to_read);
    }

    this_stripsize=TIFFReadEncodedStripGetStripSize(tif, strip, &plane);
    if (this_stripsize==((tmsize_t)(-1)))
            return((tmsize_t)(-1));

    if ((size_to_read!=(tmsize_t)(-1))&&(size_to_read<this_stripsize))
            this_stripsize=size_to_read;
    if (!TIFFFillStrip(tif,strip))
            return((tmsize_t)(-1));

    *buf = _TIFFmalloc(bufsizetoalloc);
    if (*buf == NULL) {
            TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif), "No space for strip buffer");
            return((tmsize_t)(-1));
    }
    _TIFFmemset(*buf, 0, bufsizetoalloc);

    if ((*tif->tif_decodestrip)(tif,*buf,this_stripsize,plane)<=0)
            return((tmsize_t)(-1));
    (*tif->tif_postdecode)(tif,*buf,this_stripsize);
    return(this_stripsize);


}