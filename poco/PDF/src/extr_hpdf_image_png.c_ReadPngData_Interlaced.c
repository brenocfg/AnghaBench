#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  int /*<<< orphan*/ **** png_bytep ;
struct TYPE_5__ {TYPE_1__* error; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  stream; } ;
struct TYPE_4__ {scalar_t__ error_no; } ;
typedef  size_t HPDF_UINT ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_Dict ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *****) ; 
 void* HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (int /*<<< orphan*/ *****,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_OK ; 
 scalar_t__ HPDF_Stream_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ****,int) ; 
 int png_get_image_height (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int png_get_rowbytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_read_image (int /*<<< orphan*/ ,int /*<<< orphan*/ *****) ; 

__attribute__((used)) static HPDF_STATUS
ReadPngData_Interlaced  (HPDF_Dict    image,
                         png_structp  png_ptr,
                         png_infop    info_ptr)
{
    png_uint_32 len = png_get_rowbytes(png_ptr, info_ptr);
    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
    png_bytep* row_pointers = HPDF_GetMem (image->mmgr,
                height * sizeof (png_bytep));

    if (row_pointers) {
        HPDF_UINT i;

        HPDF_MemSet (row_pointers, 0, height * sizeof (png_bytep));
        for (i = 0; i < (HPDF_UINT)height; i++) {
            row_pointers[i] = HPDF_GetMem (image->mmgr, len);

            if (image->error->error_no != HPDF_OK)
                break;
        }

        if (image->error->error_no == HPDF_OK) {
            png_read_image(png_ptr, row_pointers);
            if (image->error->error_no == HPDF_OK) {       /* add this line */
                for (i = 0; i < (HPDF_UINT)height; i++) {
                    if (HPDF_Stream_Write (image->stream, row_pointers[i], len) !=
                            HPDF_OK)
                        break;
                }
            }
        }

        /* clean up */
        for (i = 0; i < (HPDF_UINT)height; i++) {
            HPDF_FreeMem (image->mmgr, row_pointers[i]);
        }

        HPDF_FreeMem (image->mmgr, row_pointers);
    }

    return image->error->error_no;
}