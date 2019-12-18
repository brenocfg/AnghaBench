#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  int8 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_12__ {int td_sampleformat; int td_bitspersample; } ;
struct TYPE_13__ {TYPE_1__ tif_dir; int /*<<< orphan*/  tif_clientdata; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
#define  SAMPLEFORMAT_IEEEFP 130 
#define  SAMPLEFORMAT_INT 129 
#define  SAMPLEFORMAT_UINT 128 
 float TIFFClampDoubleToFloat (double) ; 
 int /*<<< orphan*/  TIFFClampDoubleToInt16 (double) ; 
 int /*<<< orphan*/  TIFFClampDoubleToInt32 (double) ; 
 int /*<<< orphan*/  TIFFClampDoubleToInt8 (double) ; 
 int /*<<< orphan*/  TIFFClampDoubleToUInt16 (double) ; 
 int TIFFClampDoubleToUInt32 (double) ; 
 int /*<<< orphan*/  TIFFClampDoubleToUInt8 (double) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int TIFFWriteDirectoryTagByteArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int TIFFWriteDirectoryTagDoubleArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,double*) ; 
 int TIFFWriteDirectoryTagFloatArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,float*) ; 
 int TIFFWriteDirectoryTagLongArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int TIFFWriteDirectoryTagSbyteArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int TIFFWriteDirectoryTagShortArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int TIFFWriteDirectoryTagSlongArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int TIFFWriteDirectoryTagSshortArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _TIFFfree (void*) ; 
 void* _TIFFmalloc (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagSampleformatArray(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, double* value)
{
	static const char module[] = "TIFFWriteDirectoryTagSampleformatArray";
	void* conv;
	uint32 i;
	int ok;
	conv = _TIFFmalloc(count*sizeof(double));
	if (conv == NULL)
	{
		TIFFErrorExt(tif->tif_clientdata, module, "Out of memory");
		return (0);
	}

	switch (tif->tif_dir.td_sampleformat)
	{
		case SAMPLEFORMAT_IEEEFP:
			if (tif->tif_dir.td_bitspersample<=32)
			{
				for (i = 0; i < count; ++i)
					((float*)conv)[i] = TIFFClampDoubleToFloat(value[i]);
				ok = TIFFWriteDirectoryTagFloatArray(tif,ndir,dir,tag,count,(float*)conv);
			}
			else
			{
				ok = TIFFWriteDirectoryTagDoubleArray(tif,ndir,dir,tag,count,value);
			}
			break;
		case SAMPLEFORMAT_INT:
			if (tif->tif_dir.td_bitspersample<=8)
			{
				for (i = 0; i < count; ++i)
					((int8*)conv)[i] = TIFFClampDoubleToInt8(value[i]);
				ok = TIFFWriteDirectoryTagSbyteArray(tif,ndir,dir,tag,count,(int8*)conv);
			}
			else if (tif->tif_dir.td_bitspersample<=16)
			{
				for (i = 0; i < count; ++i)
					((int16*)conv)[i] = TIFFClampDoubleToInt16(value[i]);
				ok = TIFFWriteDirectoryTagSshortArray(tif,ndir,dir,tag,count,(int16*)conv);
			}
			else
			{
				for (i = 0; i < count; ++i)
					((int32*)conv)[i] = TIFFClampDoubleToInt32(value[i]);
				ok = TIFFWriteDirectoryTagSlongArray(tif,ndir,dir,tag,count,(int32*)conv);
			}
			break;
		case SAMPLEFORMAT_UINT:
			if (tif->tif_dir.td_bitspersample<=8)
			{
				for (i = 0; i < count; ++i)
					((uint8*)conv)[i] = TIFFClampDoubleToUInt8(value[i]);
				ok = TIFFWriteDirectoryTagByteArray(tif,ndir,dir,tag,count,(uint8*)conv);
			}
			else if (tif->tif_dir.td_bitspersample<=16)
			{
				for (i = 0; i < count; ++i)
					((uint16*)conv)[i] = TIFFClampDoubleToUInt16(value[i]);
				ok = TIFFWriteDirectoryTagShortArray(tif,ndir,dir,tag,count,(uint16*)conv);
			}
			else
			{
				for (i = 0; i < count; ++i)
					((uint32*)conv)[i] = TIFFClampDoubleToUInt32(value[i]);
				ok = TIFFWriteDirectoryTagLongArray(tif,ndir,dir,tag,count,(uint32*)conv);
			}
			break;
		default:
			ok = 0;
	}

	_TIFFfree(conv);
	return (ok);
}