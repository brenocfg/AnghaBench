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
struct TYPE_8__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_9__ {int /*<<< orphan*/  stream; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  int HPDF_UINT ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  TYPE_2__* HPDF_Image ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 TYPE_2__* HPDF_DictStream_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_2__*,char*,char*) ; 
 scalar_t__ HPDF_Dict_AddNumber (TYPE_2__*,char*,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_XOBJECT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Stream_CcittToStream (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 

HPDF_Image
HPDF_Image_Load1BitImageFromMem  (HPDF_MMgr        mmgr,
                          const HPDF_BYTE   *buf,
                          HPDF_Xref        xref,
                          HPDF_UINT          width,
                          HPDF_UINT          height,
						  HPDF_UINT          line_width,
						  HPDF_BOOL			 top_is_first
                          )
{
    HPDF_Dict image;
    HPDF_STATUS ret = HPDF_OK;
    /* HPDF_UINT size; */

    HPDF_PTRACE ((" HPDF_Image_Load1BitImage\n"));

    image = HPDF_DictStream_New (mmgr, xref);
    if (!image)
        return NULL;

    image->header.obj_class |= HPDF_OSUBCLASS_XOBJECT;
    ret += HPDF_Dict_AddName (image, "Type", "XObject");
    ret += HPDF_Dict_AddName (image, "Subtype", "Image");
    if (ret != HPDF_OK)
        return NULL;

    /* size = width * height; */
    ret = HPDF_Dict_AddName (image, "ColorSpace", "DeviceGray");
    if (ret != HPDF_OK)
        return NULL;

    if (HPDF_Dict_AddNumber (image, "Width", width) != HPDF_OK)
        return NULL;

    if (HPDF_Dict_AddNumber (image, "Height", height) != HPDF_OK)
        return NULL;

    if (HPDF_Dict_AddNumber (image, "BitsPerComponent", 1) != HPDF_OK)
        return NULL;

    if (HPDF_Stream_CcittToStream (buf, image->stream, NULL, width, height, line_width, top_is_first) != HPDF_OK)
        return NULL;

    return image;
}