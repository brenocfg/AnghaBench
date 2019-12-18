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
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_7__ {size_t td_stripsperimage; size_t td_rowsperstrip; scalar_t__* td_stripbytecount; } ;
struct TYPE_8__ {int tif_flags; size_t tif_curstrip; size_t tif_row; scalar_t__ tif_rawcc; scalar_t__ tif_rawdataloaded; int (* tif_predecode ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * tif_rawdata; int /*<<< orphan*/ * tif_rawcp; int /*<<< orphan*/  (* tif_setupdecode ) (TYPE_2__*) ;TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int TIFF_BUF4WRITE ; 
 int TIFF_CODERSETUP ; 
 int TIFF_NOREADRAW ; 
 int /*<<< orphan*/  _TIFFFillStriles (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
TIFFStartStrip(TIFF* tif, uint32 strip)
{
	TIFFDirectory *td = &tif->tif_dir;

        if (!_TIFFFillStriles( tif ) || !tif->tif_dir.td_stripbytecount)
            return 0;

	if ((tif->tif_flags & TIFF_CODERSETUP) == 0) {
		if (!(*tif->tif_setupdecode)(tif))
			return (0);
		tif->tif_flags |= TIFF_CODERSETUP;
	}
	tif->tif_curstrip = strip;
	tif->tif_row = (strip % td->td_stripsperimage) * td->td_rowsperstrip;
        tif->tif_flags &= ~TIFF_BUF4WRITE;

	if (tif->tif_flags&TIFF_NOREADRAW)
	{
		tif->tif_rawcp = NULL;
		tif->tif_rawcc = 0;  
	}
	else
	{
		tif->tif_rawcp = tif->tif_rawdata;
		if( tif->tif_rawdataloaded > 0 )
			tif->tif_rawcc = tif->tif_rawdataloaded;
		else
			tif->tif_rawcc = (tmsize_t)td->td_stripbytecount[strip];
	}
	return ((*tif->tif_predecode)(tif,
			(uint16)(strip / td->td_stripsperimage)));
}