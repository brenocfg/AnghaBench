#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint64 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  int8 ;
typedef  int /*<<< orphan*/  int64 ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  int16 ;
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
struct TYPE_9__ {int tif_flags; } ;
struct TYPE_8__ {int tdir_type; } ;
typedef  TYPE_1__ TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 double FLT_MAX ; 
 int /*<<< orphan*/  TIFFCvtIEEEDoubleToNative (TYPE_2__*,int,...) ; 
 int TIFFReadDirEntryArray (TYPE_2__*,TYPE_1__*,int*,int,void**) ; 
 int TIFFReadDirEntryErrAlloc ; 
 int TIFFReadDirEntryErrOk ; 
 int TIFFReadDirEntryErrType ; 
 int /*<<< orphan*/  TIFFSwabArrayOfLong (int*,int) ; 
 int /*<<< orphan*/  TIFFSwabArrayOfLong8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TIFFSwabLong (int*) ; 
 int /*<<< orphan*/  TIFFSwabLong8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFFSwabShort (int /*<<< orphan*/ *) ; 
#define  TIFF_BYTE 139 
#define  TIFF_DOUBLE 138 
#define  TIFF_FLOAT 137 
#define  TIFF_LONG 136 
#define  TIFF_LONG8 135 
#define  TIFF_RATIONAL 134 
#define  TIFF_SBYTE 133 
#define  TIFF_SHORT 132 
#define  TIFF_SLONG 131 
#define  TIFF_SLONG8 130 
#define  TIFF_SRATIONAL 129 
#define  TIFF_SSHORT 128 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  _TIFFUInt64ToFloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TIFFfree (void*) ; 
 scalar_t__ _TIFFmalloc (int) ; 

__attribute__((used)) static enum TIFFReadDirEntryErr TIFFReadDirEntryFloatArray(TIFF* tif, TIFFDirEntry* direntry, float** value)
{
	enum TIFFReadDirEntryErr err;
	uint32 count;
	void* origdata;
	float* data;
	switch (direntry->tdir_type)
	{
		case TIFF_BYTE:
		case TIFF_SBYTE:
		case TIFF_SHORT:
		case TIFF_SSHORT:
		case TIFF_LONG:
		case TIFF_SLONG:
		case TIFF_LONG8:
		case TIFF_SLONG8:
		case TIFF_RATIONAL:
		case TIFF_SRATIONAL:
		case TIFF_FLOAT:
		case TIFF_DOUBLE:
			break;
		default:
			return(TIFFReadDirEntryErrType);
	}
	err=TIFFReadDirEntryArray(tif,direntry,&count,4,&origdata);
	if ((err!=TIFFReadDirEntryErrOk)||(origdata==0))
	{
		*value=0;
		return(err);
	}
	switch (direntry->tdir_type)
	{
		case TIFF_FLOAT:
			if (tif->tif_flags&TIFF_SWAB)
				TIFFSwabArrayOfLong((uint32*)origdata,count);  
			TIFFCvtIEEEDoubleToNative(tif,count,(float*)origdata);
			*value=(float*)origdata;
			return(TIFFReadDirEntryErrOk);
	}
	data=(float*)_TIFFmalloc(count*sizeof(float));
	if (data==0)
	{
		_TIFFfree(origdata);
		return(TIFFReadDirEntryErrAlloc);
	}
	switch (direntry->tdir_type)
	{
		case TIFF_BYTE:
			{
				uint8* ma;
				float* mb;
				uint32 n;
				ma=(uint8*)origdata;
				mb=data;
				for (n=0; n<count; n++)
					*mb++=(float)(*ma++);
			}
			break;
		case TIFF_SBYTE:
			{
				int8* ma;
				float* mb;
				uint32 n;
				ma=(int8*)origdata;
				mb=data;
				for (n=0; n<count; n++)
					*mb++=(float)(*ma++);
			}
			break;
		case TIFF_SHORT:
			{
				uint16* ma;
				float* mb;
				uint32 n;
				ma=(uint16*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabShort(ma);
					*mb++=(float)(*ma++);
				}
			}
			break;
		case TIFF_SSHORT:
			{
				int16* ma;
				float* mb;
				uint32 n;
				ma=(int16*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabShort((uint16*)ma);
					*mb++=(float)(*ma++);
				}
			}
			break;
		case TIFF_LONG:
			{
				uint32* ma;
				float* mb;
				uint32 n;
				ma=(uint32*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong(ma);
					*mb++=(float)(*ma++);
				}
			}
			break;
		case TIFF_SLONG:
			{
				int32* ma;
				float* mb;
				uint32 n;
				ma=(int32*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong((uint32*)ma);
					*mb++=(float)(*ma++);
				}
			}
			break;
		case TIFF_LONG8:
			{
				uint64* ma;
				float* mb;
				uint32 n;
				ma=(uint64*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong8(ma);
#if defined(__WIN32__) && (_MSC_VER < 1500)
					/*
					 * XXX: MSVC 6.0 does not support
					 * conversion of 64-bit integers into
					 * floating point values.
					 */
					*mb++ = _TIFFUInt64ToFloat(*ma++);
#else
					*mb++ = (float)(*ma++);
#endif
				}
			}
			break;
		case TIFF_SLONG8:
			{
				int64* ma;
				float* mb;
				uint32 n;
				ma=(int64*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong8((uint64*)ma);
					*mb++=(float)(*ma++);
				}
			}
			break;
		case TIFF_RATIONAL:
			{
				uint32* ma;
				uint32 maa;
				uint32 mab;
				float* mb;
				uint32 n;
				ma=(uint32*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong(ma);
					maa=*ma++;
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong(ma);
					mab=*ma++;
					if (mab==0)
						*mb++=0.0;
					else
						*mb++=(float)maa/(float)mab;
				}
			}
			break;
		case TIFF_SRATIONAL:
			{
				uint32* ma;
				int32 maa;
				uint32 mab;
				float* mb;
				uint32 n;
				ma=(uint32*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong(ma);
					maa=*(int32*)ma;
					ma++;
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong(ma);
					mab=*ma++;
					if (mab==0)
						*mb++=0.0;
					else
						*mb++=(float)maa/(float)mab;
				}
			}
			break;
		case TIFF_DOUBLE:
			{
				double* ma;
				float* mb;
				uint32 n;
				if (tif->tif_flags&TIFF_SWAB)
					TIFFSwabArrayOfLong8((uint64*)origdata,count);
				TIFFCvtIEEEDoubleToNative(tif,count,(double*)origdata);
				ma=(double*)origdata;
				mb=data;
				for (n=0; n<count; n++)
                                {
                                    double val = *ma++;
                                    if( val > FLT_MAX )
                                        val = FLT_MAX;
                                    else if( val < -FLT_MAX )
                                        val = -FLT_MAX;
                                    *mb++=(float)val;
                                }
			}
			break;
	}
	_TIFFfree(origdata);
	*value=data;
	return(TIFFReadDirEntryErrOk);
}