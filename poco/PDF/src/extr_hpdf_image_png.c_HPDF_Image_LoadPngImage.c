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
typedef  int /*<<< orphan*/  png_size_t ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_11__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_13__ {TYPE_1__ header; } ;
struct TYPE_12__ {int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_MMgr ;
typedef  TYPE_3__* HPDF_Image ;
typedef  TYPE_3__* HPDF_Dict ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 TYPE_3__* HPDF_DictStream_New (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  HPDF_INVALID_PNG_IMAGE ; 
 int /*<<< orphan*/  HPDF_MemSet (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_XOBJECT ; 
 int HPDF_PNG_BYTES_TO_CHECK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ LoadPngData (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ png_sig_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

HPDF_Image
HPDF_Image_LoadPngImage  (HPDF_MMgr        mmgr,
                          HPDF_Stream      png_data,
                          HPDF_Xref        xref,
                          HPDF_BOOL        delayed_loading)
{
    HPDF_STATUS ret;
    HPDF_Dict image;
    png_byte header[HPDF_PNG_BYTES_TO_CHECK];
    HPDF_UINT len = HPDF_PNG_BYTES_TO_CHECK;

    HPDF_PTRACE ((" HPDF_Image_LoadPngImage\n"));

    HPDF_MemSet (header, 0x00, HPDF_PNG_BYTES_TO_CHECK);
    ret = HPDF_Stream_Read (png_data, header, &len);
    if (ret != HPDF_OK ||
            png_sig_cmp (header, (png_size_t)0, HPDF_PNG_BYTES_TO_CHECK)) {
        HPDF_SetError (mmgr->error, HPDF_INVALID_PNG_IMAGE, 0);
        return NULL;
    }

    image = HPDF_DictStream_New (mmgr, xref);
    if (!image)
        return NULL;

    image->header.obj_class |= HPDF_OSUBCLASS_XOBJECT;
    ret += HPDF_Dict_AddName (image, "Type", "XObject");
    ret += HPDF_Dict_AddName (image, "Subtype", "Image");
    if (ret != HPDF_OK)
        return NULL;

    if (LoadPngData (image, xref, png_data, delayed_loading) != HPDF_OK)
        return NULL;

    return image;
}