#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ uint16 ;
typedef  scalar_t__ int8 ;
typedef  scalar_t__ int64 ;
typedef  scalar_t__ int32 ;
typedef  scalar_t__ int16 ;
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
struct TYPE_15__ {int tdir_count; int tdir_type; } ;
typedef  TYPE_1__ TIFFDirEntry ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 double FLT_MAX ; 
 double FLT_MIN ; 
 int /*<<< orphan*/  TIFFReadDirEntryCheckedByte (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 int TIFFReadDirEntryCheckedDouble (int /*<<< orphan*/ *,TYPE_1__*,double*) ; 
 int /*<<< orphan*/  TIFFReadDirEntryCheckedFloat (int /*<<< orphan*/ *,TYPE_1__*,float*) ; 
 int /*<<< orphan*/  TIFFReadDirEntryCheckedLong (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 int TIFFReadDirEntryCheckedLong8 (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 int TIFFReadDirEntryCheckedRational (int /*<<< orphan*/ *,TYPE_1__*,double*) ; 
 int /*<<< orphan*/  TIFFReadDirEntryCheckedSbyte (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  TIFFReadDirEntryCheckedShort (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  TIFFReadDirEntryCheckedSlong (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 int TIFFReadDirEntryCheckedSlong8 (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 int TIFFReadDirEntryCheckedSrational (int /*<<< orphan*/ *,TYPE_1__*,double*) ; 
 int /*<<< orphan*/  TIFFReadDirEntryCheckedSshort (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 int TIFFReadDirEntryErrCount ; 
 int TIFFReadDirEntryErrOk ; 
 int TIFFReadDirEntryErrRange ; 
 int TIFFReadDirEntryErrType ; 
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
 float _TIFFUInt64ToFloat (scalar_t__) ; 

__attribute__((used)) static enum TIFFReadDirEntryErr TIFFReadDirEntryFloat(TIFF* tif, TIFFDirEntry* direntry, float* value)
{
	enum TIFFReadDirEntryErr err;
	if (direntry->tdir_count!=1)
		return(TIFFReadDirEntryErrCount);
	switch (direntry->tdir_type)
	{
		case TIFF_BYTE:
			{
				uint8 m;
				TIFFReadDirEntryCheckedByte(tif,direntry,&m);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_SBYTE:
			{
				int8 m;
				TIFFReadDirEntryCheckedSbyte(tif,direntry,&m);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_SHORT:
			{
				uint16 m;
				TIFFReadDirEntryCheckedShort(tif,direntry,&m);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_SSHORT:
			{
				int16 m;
				TIFFReadDirEntryCheckedSshort(tif,direntry,&m);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_LONG:
			{
				uint32 m;
				TIFFReadDirEntryCheckedLong(tif,direntry,&m);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_SLONG:
			{
				int32 m;
				TIFFReadDirEntryCheckedSlong(tif,direntry,&m);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_LONG8:
			{
				uint64 m;
				err=TIFFReadDirEntryCheckedLong8(tif,direntry,&m);
				if (err!=TIFFReadDirEntryErrOk)
					return(err);
#if defined(__WIN32__) && (_MSC_VER < 1500)
				/*
				 * XXX: MSVC 6.0 does not support conversion
				 * of 64-bit integers into floating point
				 * values.
				 */
				*value = _TIFFUInt64ToFloat(m);
#else
				*value=(float)m;
#endif
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_SLONG8:
			{
				int64 m;
				err=TIFFReadDirEntryCheckedSlong8(tif,direntry,&m);
				if (err!=TIFFReadDirEntryErrOk)
					return(err);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_RATIONAL:
			{
				double m;
				err=TIFFReadDirEntryCheckedRational(tif,direntry,&m);
				if (err!=TIFFReadDirEntryErrOk)
					return(err);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_SRATIONAL:
			{
				double m;
				err=TIFFReadDirEntryCheckedSrational(tif,direntry,&m);
				if (err!=TIFFReadDirEntryErrOk)
					return(err);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_FLOAT:
			TIFFReadDirEntryCheckedFloat(tif,direntry,value);
			return(TIFFReadDirEntryErrOk);
		case TIFF_DOUBLE:
			{
				double m;
				err=TIFFReadDirEntryCheckedDouble(tif,direntry,&m);
				if (err!=TIFFReadDirEntryErrOk)
					return(err);
				if ((m > FLT_MAX) || (m < FLT_MIN))
					return(TIFFReadDirEntryErrRange);
				*value=(float)m;
				return(TIFFReadDirEntryErrOk);
			}
		default:
			return(TIFFReadDirEntryErrType);
	}
}