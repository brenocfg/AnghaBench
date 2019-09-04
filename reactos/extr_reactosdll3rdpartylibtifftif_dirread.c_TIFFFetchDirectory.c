#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int uint16 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_13__ {int tif_diroff; int tif_flags; scalar_t__ tif_size; scalar_t__ tif_base; int /*<<< orphan*/  tif_clientdata; int /*<<< orphan*/  tif_name; } ;
struct TYPE_11__ {void* toff_long8; } ;
struct TYPE_12__ {int tdir_tag; int tdir_type; int tdir_count; TYPE_1__ tdir_offset; } ;
typedef  TYPE_2__ TIFFDirEntry ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  ReadOK (TYPE_3__*,int*,int) ; 
 int /*<<< orphan*/  SeekOK (TYPE_3__*,int) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 void* TIFFReadUInt64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFFSwabLong (int*) ; 
 int /*<<< orphan*/  TIFFSwabLong8 (int*) ; 
 int /*<<< orphan*/  TIFFSwabShort (int*) ; 
 int TIFF_BIGTIFF ; 
 int TIFF_SWAB ; 
 void* _TIFFCheckMalloc (TYPE_3__*,int,int,char*) ; 
 int /*<<< orphan*/  _TIFFfree (void*) ; 
 int /*<<< orphan*/  _TIFFmemcpy (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  assert (TYPE_2__**) ; 
 int /*<<< orphan*/  isMapped (TYPE_3__*) ; 

__attribute__((used)) static uint16
TIFFFetchDirectory(TIFF* tif, uint64 diroff, TIFFDirEntry** pdir,
                   uint64 *nextdiroff)
{
	static const char module[] = "TIFFFetchDirectory";

	void* origdir;
	uint16 dircount16;
	uint32 dirsize;
	TIFFDirEntry* dir;
	uint8* ma;
	TIFFDirEntry* mb;
	uint16 n;

	assert(pdir);

	tif->tif_diroff = diroff;
	if (nextdiroff)
		*nextdiroff = 0;
	if (!isMapped(tif)) {
		if (!SeekOK(tif, tif->tif_diroff)) {
			TIFFErrorExt(tif->tif_clientdata, module,
				"%s: Seek error accessing TIFF directory",
				tif->tif_name);
			return 0;
		}
		if (!(tif->tif_flags&TIFF_BIGTIFF))
		{
			if (!ReadOK(tif, &dircount16, sizeof (uint16))) {
				TIFFErrorExt(tif->tif_clientdata, module,
				    "%s: Can not read TIFF directory count",
				    tif->tif_name);
				return 0;
			}
			if (tif->tif_flags & TIFF_SWAB)
				TIFFSwabShort(&dircount16);
			if (dircount16>4096)
			{
				TIFFErrorExt(tif->tif_clientdata, module,
				    "Sanity check on directory count failed, this is probably not a valid IFD offset");
				return 0;
			}
			dirsize = 12;
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
			if (dircount64>4096)
			{
				TIFFErrorExt(tif->tif_clientdata, module,
				    "Sanity check on directory count failed, this is probably not a valid IFD offset");
				return 0;
			}
			dircount16 = (uint16)dircount64;
			dirsize = 20;
		}
		origdir = _TIFFCheckMalloc(tif, dircount16,
		    dirsize, "to read TIFF directory");
		if (origdir == NULL)
			return 0;
		if (!ReadOK(tif, origdir, (tmsize_t)(dircount16*dirsize))) {
			TIFFErrorExt(tif->tif_clientdata, module,
				"%.100s: Can not read TIFF directory",
				tif->tif_name);
			_TIFFfree(origdir);
			return 0;
		}
		/*
		 * Read offset to next directory for sequential scans if
		 * needed.
		 */
		if (nextdiroff)
		{
			if (!(tif->tif_flags&TIFF_BIGTIFF))
			{
				uint32 nextdiroff32;
				if (!ReadOK(tif, &nextdiroff32, sizeof(uint32)))
					nextdiroff32 = 0;
				if (tif->tif_flags&TIFF_SWAB)
					TIFFSwabLong(&nextdiroff32);
				*nextdiroff=nextdiroff32;
			} else {
				if (!ReadOK(tif, nextdiroff, sizeof(uint64)))
					*nextdiroff = 0;
				if (tif->tif_flags&TIFF_SWAB)
					TIFFSwabLong8(nextdiroff);
			}
		}
	} else {
		tmsize_t m;
		tmsize_t off = (tmsize_t) tif->tif_diroff;
		if ((uint64)off!=tif->tif_diroff)
		{
			TIFFErrorExt(tif->tif_clientdata,module,"Can not read TIFF directory count");
			return(0);
		}

		/*
		 * Check for integer overflow when validating the dir_off,
		 * otherwise a very high offset may cause an OOB read and
		 * crash the client. Make two comparisons instead of
		 *
		 *  off + sizeof(uint16) > tif->tif_size
		 *
		 * to avoid overflow.
		 */
		if (!(tif->tif_flags&TIFF_BIGTIFF))
		{
			m=off+sizeof(uint16);
			if ((m<off)||(m<(tmsize_t)sizeof(uint16))||(m>tif->tif_size)) {
				TIFFErrorExt(tif->tif_clientdata, module,
					"Can not read TIFF directory count");
				return 0;
			} else {
				_TIFFmemcpy(&dircount16, tif->tif_base + off,
					    sizeof(uint16));
			}
			off += sizeof (uint16);
			if (tif->tif_flags & TIFF_SWAB)
				TIFFSwabShort(&dircount16);
			if (dircount16>4096)
			{
				TIFFErrorExt(tif->tif_clientdata, module,
				    "Sanity check on directory count failed, this is probably not a valid IFD offset");
				return 0;
			}
			dirsize = 12;
		}
		else
		{
			uint64 dircount64;
			m=off+sizeof(uint64);
			if ((m<off)||(m<(tmsize_t)sizeof(uint64))||(m>tif->tif_size)) {
				TIFFErrorExt(tif->tif_clientdata, module,
					"Can not read TIFF directory count");
				return 0;
			} else {
				_TIFFmemcpy(&dircount64, tif->tif_base + off,
					    sizeof(uint64));
			}
			off += sizeof (uint64);
			if (tif->tif_flags & TIFF_SWAB)
				TIFFSwabLong8(&dircount64);
			if (dircount64>4096)
			{
				TIFFErrorExt(tif->tif_clientdata, module,
				    "Sanity check on directory count failed, this is probably not a valid IFD offset");
				return 0;
			}
			dircount16 = (uint16)dircount64;
			dirsize = 20;
		}
		if (dircount16 == 0 )
		{
			TIFFErrorExt(tif->tif_clientdata, module,
			             "Sanity check on directory count failed, zero tag directories not supported");
			return 0;
		}
		origdir = _TIFFCheckMalloc(tif, dircount16,
						dirsize,
						"to read TIFF directory");
		if (origdir == NULL)
			return 0;
		m=off+dircount16*dirsize;
		if ((m<off)||(m<(tmsize_t)(dircount16*dirsize))||(m>tif->tif_size)) {
			TIFFErrorExt(tif->tif_clientdata, module,
				     "Can not read TIFF directory");
			_TIFFfree(origdir);
			return 0;
		} else {
			_TIFFmemcpy(origdir, tif->tif_base + off,
				    dircount16 * dirsize);
		}
		if (nextdiroff) {
			off += dircount16 * dirsize;
			if (!(tif->tif_flags&TIFF_BIGTIFF))
			{
				uint32 nextdiroff32;
				m=off+sizeof(uint32);
				if ((m<off)||(m<(tmsize_t)sizeof(uint32))||(m>tif->tif_size))
					nextdiroff32 = 0;
				else
					_TIFFmemcpy(&nextdiroff32, tif->tif_base + off,
						    sizeof (uint32));
				if (tif->tif_flags&TIFF_SWAB)
					TIFFSwabLong(&nextdiroff32);
				*nextdiroff = nextdiroff32;
			}
			else
			{
				m=off+sizeof(uint64);
				if ((m<off)||(m<(tmsize_t)sizeof(uint64))||(m>tif->tif_size))
					*nextdiroff = 0;
				else
					_TIFFmemcpy(nextdiroff, tif->tif_base + off,
						    sizeof (uint64));
				if (tif->tif_flags&TIFF_SWAB)
					TIFFSwabLong8(nextdiroff);
			}
		}
	}
	dir = (TIFFDirEntry*)_TIFFCheckMalloc(tif, dircount16,
						sizeof(TIFFDirEntry),
						"to read TIFF directory");
	if (dir==0)
	{
		_TIFFfree(origdir);
		return 0;
	}
	ma=(uint8*)origdir;
	mb=dir;
	for (n=0; n<dircount16; n++)
	{
		if (tif->tif_flags&TIFF_SWAB)
			TIFFSwabShort((uint16*)ma);
		mb->tdir_tag=*(uint16*)ma;
		ma+=sizeof(uint16);
		if (tif->tif_flags&TIFF_SWAB)
			TIFFSwabShort((uint16*)ma);
		mb->tdir_type=*(uint16*)ma;
		ma+=sizeof(uint16);
		if (!(tif->tif_flags&TIFF_BIGTIFF))
		{
			if (tif->tif_flags&TIFF_SWAB)
				TIFFSwabLong((uint32*)ma);
			mb->tdir_count=(uint64)(*(uint32*)ma);
			ma+=sizeof(uint32);
			*(uint32*)(&mb->tdir_offset)=*(uint32*)ma;
			ma+=sizeof(uint32);
		}
		else
		{
			if (tif->tif_flags&TIFF_SWAB)
				TIFFSwabLong8((uint64*)ma);
                        mb->tdir_count=TIFFReadUInt64(ma);
			ma+=sizeof(uint64);
			mb->tdir_offset.toff_long8=TIFFReadUInt64(ma);
			ma+=sizeof(uint64);
		}
		mb++;
	}
	_TIFFfree(origdir);
	*pdir = dir;
	return dircount16;
}