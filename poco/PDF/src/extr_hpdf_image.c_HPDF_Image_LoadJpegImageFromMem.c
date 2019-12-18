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
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  TYPE_1__* HPDF_MMgr ;
typedef  int /*<<< orphan*/ * HPDF_Image ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_INVALID_STREAM ; 
 int /*<<< orphan*/ * HPDF_Image_LoadJpegImage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MemStream_New (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_RaiseError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Stream_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Stream_Validate (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

HPDF_Image
HPDF_Image_LoadJpegImageFromMem  (HPDF_MMgr    mmgr,
                            const HPDF_BYTE   *buf,
                                  HPDF_UINT    size,
                                  HPDF_Xref    xref)
{
	HPDF_Stream jpeg_data;
	HPDF_Image image;

	HPDF_PTRACE ((" HPDF_Image_LoadJpegImageFromMem\n"));

	jpeg_data = HPDF_MemStream_New(mmgr,size);
	if (!HPDF_Stream_Validate (jpeg_data)) {
		HPDF_RaiseError (mmgr->error, HPDF_INVALID_STREAM, 0);
		return NULL;
	}

	if (HPDF_Stream_Write (jpeg_data, buf, size) != HPDF_OK) {
		HPDF_Stream_Free (jpeg_data);
		return NULL;
	}

	image = HPDF_Image_LoadJpegImage(mmgr,jpeg_data,xref);

	/* destroy file stream */
	HPDF_Stream_Free (jpeg_data);

	return image;
}