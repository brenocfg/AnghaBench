#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ uint16 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_6__ {scalar_t__ td_nstrips; scalar_t__ td_rowsperstrip; scalar_t__ td_imagelength; } ;
struct TYPE_7__ {int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFCheckRead (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,unsigned long,unsigned long) ; 
 scalar_t__ TIFFVStripSize (TYPE_2__*,scalar_t__) ; 
 scalar_t__ TIFFhowmany_32_maxuint_compat (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tmsize_t TIFFReadEncodedStripGetStripSize(TIFF* tif, uint32 strip, uint16* pplane)
{
	static const char module[] = "TIFFReadEncodedStrip";
	TIFFDirectory *td = &tif->tif_dir;
	uint32 rowsperstrip;
	uint32 stripsperplane;
	uint32 stripinplane;
	uint32 rows;
	tmsize_t stripsize;
	if (!TIFFCheckRead(tif,0))
		return((tmsize_t)(-1));
	if (strip>=td->td_nstrips)
	{
		TIFFErrorExt(tif->tif_clientdata,module,
		    "%lu: Strip out of range, max %lu",(unsigned long)strip,
		    (unsigned long)td->td_nstrips);
		return((tmsize_t)(-1));
	}

	rowsperstrip=td->td_rowsperstrip;
	if (rowsperstrip>td->td_imagelength)
		rowsperstrip=td->td_imagelength;
	stripsperplane= TIFFhowmany_32_maxuint_compat(td->td_imagelength, rowsperstrip);
	stripinplane=(strip%stripsperplane);
	if( pplane ) *pplane=(uint16)(strip/stripsperplane);
	rows=td->td_imagelength-stripinplane*rowsperstrip;
	if (rows>rowsperstrip)
		rows=rowsperstrip;
	stripsize=TIFFVStripSize(tif,rows);
	if (stripsize==0)
		return((tmsize_t)(-1));
	return stripsize;
}