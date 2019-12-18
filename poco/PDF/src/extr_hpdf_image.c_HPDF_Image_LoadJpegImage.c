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
struct TYPE_9__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  filter; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  scalar_t__ HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  TYPE_2__* HPDF_Image ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 TYPE_2__* HPDF_DictStream_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_2__*,char*,char*) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_XOBJECT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 int HPDF_STREAM_BUF_SIZ ; 
 scalar_t__ HPDF_STREAM_EOF ; 
 int /*<<< orphan*/  HPDF_STREAM_FILTER_DCT_DECODE ; 
 scalar_t__ HPDF_Stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ HPDF_Stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LoadJpegHeader (TYPE_2__*,int /*<<< orphan*/ ) ; 

HPDF_Image
HPDF_Image_LoadJpegImage  (HPDF_MMgr        mmgr,
                           HPDF_Stream      jpeg_data,
                           HPDF_Xref        xref)
{
    HPDF_Dict image;
    HPDF_STATUS ret = HPDF_OK;

    HPDF_PTRACE ((" HPDF_Image_LoadJpegImage\n"));

    image = HPDF_DictStream_New (mmgr, xref);
    if (!image)
        return NULL;

    image->header.obj_class |= HPDF_OSUBCLASS_XOBJECT;

    /* add requiered elements */
    image->filter = HPDF_STREAM_FILTER_DCT_DECODE;
    ret += HPDF_Dict_AddName (image, "Type", "XObject");
    ret += HPDF_Dict_AddName (image, "Subtype", "Image");
    if (ret != HPDF_OK)
        return NULL;

    if (LoadJpegHeader (image, jpeg_data) != HPDF_OK)
        return NULL;

    if (HPDF_Stream_Seek (jpeg_data, 0, HPDF_SEEK_SET) != HPDF_OK)
        return NULL;

    for (;;) {
        HPDF_BYTE buf[HPDF_STREAM_BUF_SIZ];
        HPDF_UINT len = HPDF_STREAM_BUF_SIZ;
        HPDF_STATUS ret = HPDF_Stream_Read (jpeg_data, buf,
                &len);

        if (ret != HPDF_OK) {
            if (ret == HPDF_STREAM_EOF) {
                if (len > 0) {
                    ret = HPDF_Stream_Write (image->stream, buf, len);
                    if (ret != HPDF_OK)
                        return NULL;
                }
                break;
            } else
                return NULL;
        }

        if (HPDF_Stream_Write (image->stream, buf, len) != HPDF_OK)
            return NULL;
    }

    return image;
}