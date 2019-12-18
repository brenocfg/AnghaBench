#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TIFFField ;
typedef  int /*<<< orphan*/  TIFFDataType ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/ * TIFFFindField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _TIFFCreateAnonField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TIFFMergeFields (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

const TIFFField*
_TIFFFindOrRegisterField(TIFF *tif, uint32 tag, TIFFDataType dt)

{
	const TIFFField *fld;

	fld = TIFFFindField(tif, tag, dt);
	if (fld == NULL) {
		fld = _TIFFCreateAnonField(tif, tag, dt);
		if (!_TIFFMergeFields(tif, fld, 1))
			return NULL;
	}

	return fld;
}