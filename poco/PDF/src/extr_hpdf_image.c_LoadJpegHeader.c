#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  error; } ;
struct TYPE_9__ {int /*<<< orphan*/  error; } ;
typedef  int HPDF_UINT16 ;
typedef  int HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_Image ;
typedef  int HPDF_BYTE ;
typedef  int /*<<< orphan*/  HPDF_Array ;

/* Variables and functions */
 char* COL_CMYK ; 
 char* COL_GRAY ; 
 char* COL_RGB ; 
 scalar_t__ HPDF_Array_Add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_AddNumber (TYPE_2__*,char*,int) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_INVALID_JPEG_DATA ; 
 int /*<<< orphan*/  HPDF_Name_New (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  HPDF_Number_New (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_CUR ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Read (TYPE_1__*,int*,int*) ; 
 scalar_t__ HPDF_Stream_Seek (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_UInt16Swap (int*) ; 
 int /*<<< orphan*/  HPDF_UNSUPPORTED_JPEG_FORMAT ; 

__attribute__((used)) static HPDF_STATUS
LoadJpegHeader (HPDF_Image   image,
                HPDF_Stream  stream)
{
    HPDF_UINT16 tag;
    HPDF_UINT16 height;
    HPDF_UINT16 width;
    HPDF_BYTE precision;
    HPDF_BYTE num_components;
    const char *color_space_name;
    HPDF_UINT len;
    HPDF_STATUS ret;
    HPDF_Array array;

    HPDF_PTRACE ((" HPDF_Image_LoadJpegHeader\n"));

    len = 2;
    if (HPDF_Stream_Read (stream, (HPDF_BYTE *)&tag, &len) != HPDF_OK)
        return HPDF_Error_GetCode (stream->error);

    HPDF_UInt16Swap (&tag);
    if (tag != 0xFFD8)
        return HPDF_INVALID_JPEG_DATA;

    /* find SOF record */
    for (;;) {
        HPDF_UINT16 size;

        len = 2;
        if (HPDF_Stream_Read (stream, (HPDF_BYTE *)&tag,  &len) != HPDF_OK)
            return HPDF_Error_GetCode (stream->error);

        HPDF_UInt16Swap (&tag);

        len = 2;
        if (HPDF_Stream_Read (stream, (HPDF_BYTE *)&size,  &len) != HPDF_OK)
            return HPDF_Error_GetCode (stream->error);

        HPDF_UInt16Swap (&size);

        HPDF_PTRACE (("tag=%04X size=%u\n", tag, size));

        if (tag == 0xFFC0 || tag == 0xFFC1 ||
                tag == 0xFFC2 || tag == 0xFFC9) {

            len = 1;
            if (HPDF_Stream_Read (stream, (HPDF_BYTE *)&precision, &len) !=
                    HPDF_OK)
                return HPDF_Error_GetCode (stream->error);

            len = 2;
            if (HPDF_Stream_Read (stream, (HPDF_BYTE *)&height, &len) !=
                    HPDF_OK)
                return HPDF_Error_GetCode (stream->error);

            HPDF_UInt16Swap (&height);

            len = 2;
            if (HPDF_Stream_Read (stream, (HPDF_BYTE *)&width, &len) != HPDF_OK)
                return HPDF_Error_GetCode (stream->error);

             HPDF_UInt16Swap (&width);

           len = 1;
            if (HPDF_Stream_Read (stream, (HPDF_BYTE *)&num_components, &len) !=
                    HPDF_OK)
                return HPDF_Error_GetCode (stream->error);

            break;
        } else if ((tag | 0x00FF) != 0xFFFF)
            /* lost marker */
            return HPDF_SetError (image->error, HPDF_UNSUPPORTED_JPEG_FORMAT,
                    0);

        if (HPDF_Stream_Seek (stream, size - 2, HPDF_SEEK_CUR) != HPDF_OK)
                return HPDF_Error_GetCode (stream->error);
    }

    if (HPDF_Dict_AddNumber (image, "Height", height) != HPDF_OK)
        return HPDF_Error_GetCode (stream->error);

    if (HPDF_Dict_AddNumber (image, "Width", width) != HPDF_OK)
        return HPDF_Error_GetCode (stream->error);

    /* classification of RGB and CMYK is less than perfect
     * YCbCr and YCCK are classified into RGB or CMYK.
     *
     * It is necessary to read APP14 data to distinguish colorspace perfectly.

     */
    switch (num_components) {
        case 1:
            color_space_name = COL_GRAY;
            break;
        case 3:
            color_space_name = COL_RGB;
            break;
        case 4:
            array = HPDF_Array_New (image->mmgr);
            if (!array)
                return HPDF_Error_GetCode (stream->error);

            ret = HPDF_Dict_Add (image, "Decode", array);
            if (ret != HPDF_OK)
                return HPDF_Error_GetCode (stream->error);

            ret += HPDF_Array_Add (array, HPDF_Number_New (image->mmgr, 1));
            ret += HPDF_Array_Add (array, HPDF_Number_New (image->mmgr, 0));
            ret += HPDF_Array_Add (array, HPDF_Number_New (image->mmgr, 1));
            ret += HPDF_Array_Add (array, HPDF_Number_New (image->mmgr, 0));
            ret += HPDF_Array_Add (array, HPDF_Number_New (image->mmgr, 1));
            ret += HPDF_Array_Add (array, HPDF_Number_New (image->mmgr, 0));
            ret += HPDF_Array_Add (array, HPDF_Number_New (image->mmgr, 1));
            ret += HPDF_Array_Add (array, HPDF_Number_New (image->mmgr, 0));

            if (ret != HPDF_OK)
                return HPDF_Error_GetCode (stream->error);

            color_space_name = COL_CMYK;

            break;
        default:
            return HPDF_SetError (image->error, HPDF_UNSUPPORTED_JPEG_FORMAT,
                    0);
    }

    if (HPDF_Dict_Add (image, "ColorSpace",
                HPDF_Name_New (image->mmgr, color_space_name)) != HPDF_OK)
        return HPDF_Error_GetCode (stream->error);

    if (HPDF_Dict_Add (image, "BitsPerComponent",
                HPDF_Number_New (image->mmgr, precision)) != HPDF_OK)
        return HPDF_Error_GetCode (stream->error);

    return HPDF_OK;
}