#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_5__ {int tif_flags; int /*<<< orphan*/  tif_clientdata; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int TIFFWriteDirectoryTagCheckedIfd8Array (TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int TIFFWriteDirectoryTagCheckedIfdArray (TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int TIFF_BIGTIFF ; 
 int /*<<< orphan*/  _TIFFfree (int*) ; 
 int* _TIFFmalloc (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagIfdIfd8Array(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, uint64* value)
{
    static const char module[] = "TIFFWriteDirectoryTagIfdIfd8Array";
    uint64* ma;
    uint32 mb;
    uint32* p;
    uint32* q;
    int o;

    /* is this just a counting pass? */
    if (dir==NULL)
    {
        (*ndir)++;
        return(1);
    }

    /* We always write IFD8 for BigTIFF, no checking needed. */
    if( tif->tif_flags&TIFF_BIGTIFF )
        return TIFFWriteDirectoryTagCheckedIfd8Array(tif,ndir,dir,
                                                     tag,count,value);

    /*
    ** For classic tiff we want to verify everything is in range for IFD
    ** and convert to long format.
    */

    p = _TIFFmalloc(count*sizeof(uint32));
    if (p==NULL)
    {
        TIFFErrorExt(tif->tif_clientdata,module,"Out of memory");
        return(0);
    }

    for (q=p, ma=value, mb=0; mb<count; ma++, mb++, q++)
    {
        if (*ma>0xFFFFFFFF)
        {
            TIFFErrorExt(tif->tif_clientdata,module,
                         "Attempt to write value larger than 0xFFFFFFFF in Classic TIFF file.");
            _TIFFfree(p);
            return(0);
        }
        *q= (uint32)(*ma);
    }

    o=TIFFWriteDirectoryTagCheckedIfdArray(tif,ndir,dir,tag,count,p);
    _TIFFfree(p);

    return(o);
}