#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_7__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_1__ png_color ;
struct TYPE_9__ {int /*<<< orphan*/  error_no; } ;
struct TYPE_8__ {TYPE_4__* error; int /*<<< orphan*/  mmgr; } ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int HPDF_INT ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  scalar_t__ HPDF_Binary ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;
typedef  scalar_t__ HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Add (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_Array_AddName (scalar_t__,char*) ; 
 int /*<<< orphan*/  HPDF_Array_AddNumber (scalar_t__,int) ; 
 scalar_t__ HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Binary_New (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HPDF_CANNOT_GET_PALLET ; 
 int /*<<< orphan*/  HPDF_Dict_Add (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_LIBPNG_ERROR ; 
 int /*<<< orphan*/  HPDF_SetError (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PNG_INFO_PLTE ; 
 scalar_t__ png_get_PLTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int*) ; 

__attribute__((used)) static HPDF_STATUS
CreatePallet (HPDF_Dict    image,
              png_structp  png_ptr,
              png_infop    info_ptr)
{
    HPDF_INT num_pl = 0;
    png_color *src_pl = NULL;
    HPDF_BYTE *ppallet;
    HPDF_BYTE *p;
    HPDF_UINT i;
    HPDF_Array array;

    /* png_get_PLTE does not call PngErrorFunc even if it failed.
     * so we call HPDF_Set_Error to set error-code.
     */
    if (png_get_PLTE(png_ptr, info_ptr, (png_color**)&src_pl, &num_pl) !=
            PNG_INFO_PLTE)
        return HPDF_SetError (image->error, HPDF_LIBPNG_ERROR,
                    HPDF_CANNOT_GET_PALLET);


    /* make a pallet array for indexed image. */
    ppallet = HPDF_GetMem (image->mmgr, num_pl * 3);
    if (!ppallet)
        return image->error->error_no;

    p = ppallet;
    for (i = 0; i < num_pl; i++, src_pl++) {
        *p++ = src_pl->red;
        *p++ = src_pl->green;
        *p++ = src_pl->blue;
    }

    array = HPDF_Array_New (image->mmgr);
    if (array) {
        HPDF_Binary b;

        HPDF_Dict_Add (image, "ColorSpace", array);

        HPDF_Array_AddName (array, "Indexed");
        HPDF_Array_AddName (array, "DeviceRGB");
        HPDF_Array_AddNumber (array, num_pl - 1);

        b = HPDF_Binary_New (image->mmgr, ppallet, num_pl * 3);
        if (b)
            HPDF_Array_Add (array, b);
    }

    HPDF_FreeMem (image->mmgr, ppallet);

    return image->error->error_no;
}