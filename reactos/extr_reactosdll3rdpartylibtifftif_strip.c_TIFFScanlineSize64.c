#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_7__ {scalar_t__ td_planarconfig; scalar_t__ td_photometric; int td_samplesperpixel; int td_imagewidth; int td_bitspersample; } ;
struct TYPE_8__ {int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ PHOTOMETRIC_YCBCR ; 
 scalar_t__ PLANARCONFIG_CONTIG ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  TIFFGetFieldDefaulted (TYPE_2__*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  TIFFTAG_YCBCRSUBSAMPLING ; 
 int TIFFhowmany_32 (int,int) ; 
 int TIFFhowmany_64 (int,int) ; 
 int _TIFFMultiply64 (TYPE_2__*,int,int,char const*) ; 
 int /*<<< orphan*/  isUpSampled (TYPE_2__*) ; 

uint64
TIFFScanlineSize64(TIFF* tif)
{
	static const char module[] = "TIFFScanlineSize64";
	TIFFDirectory *td = &tif->tif_dir;
	uint64 scanline_size;
	if (td->td_planarconfig==PLANARCONFIG_CONTIG)
	{
		if ((td->td_photometric==PHOTOMETRIC_YCBCR)&&
		    (td->td_samplesperpixel==3)&&
		    (!isUpSampled(tif)))
		{
			uint16 ycbcrsubsampling[2];
			uint16 samplingblock_samples;
			uint32 samplingblocks_hor;
			uint64 samplingrow_samples;
			uint64 samplingrow_size;
			if(td->td_samplesperpixel!=3)
			{
                            TIFFErrorExt(tif->tif_clientdata,module,
                                         "Invalid td_samplesperpixel value");
                            return 0;
			}
			TIFFGetFieldDefaulted(tif,TIFFTAG_YCBCRSUBSAMPLING,
                                              ycbcrsubsampling+0,
                                              ycbcrsubsampling+1);
			if (((ycbcrsubsampling[0]!=1)&&(ycbcrsubsampling[0]!=2)&&(ycbcrsubsampling[0]!=4)) ||
			    ((ycbcrsubsampling[1]!=1)&&(ycbcrsubsampling[1]!=2)&&(ycbcrsubsampling[1]!=4)))
			{
                            TIFFErrorExt(tif->tif_clientdata,module,
                                         "Invalid YCbCr subsampling");
                            return 0;
			}
			samplingblock_samples = ycbcrsubsampling[0]*ycbcrsubsampling[1]+2;
			samplingblocks_hor = TIFFhowmany_32(td->td_imagewidth,ycbcrsubsampling[0]);
			samplingrow_samples = _TIFFMultiply64(tif,samplingblocks_hor,samplingblock_samples,module);
			samplingrow_size = TIFFhowmany_64(_TIFFMultiply64(tif,samplingrow_samples,td->td_bitspersample,module),8);
			scanline_size = (samplingrow_size/ycbcrsubsampling[1]);
		}
		else
		{
			uint64 scanline_samples;
			scanline_samples=_TIFFMultiply64(tif,td->td_imagewidth,td->td_samplesperpixel,module);
			scanline_size=TIFFhowmany_64(_TIFFMultiply64(tif,scanline_samples,td->td_bitspersample,module),8);
		}
	}
	else
        {
		scanline_size=TIFFhowmany_64(_TIFFMultiply64(tif,td->td_imagewidth,td->td_bitspersample,module),8);
        }
        if (scanline_size == 0)
        {
                TIFFErrorExt(tif->tif_clientdata,module,"Computed scanline size is zero");
                return 0;
        }
	return(scanline_size);
}