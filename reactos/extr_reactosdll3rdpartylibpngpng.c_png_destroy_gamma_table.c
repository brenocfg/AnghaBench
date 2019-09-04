#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
struct TYPE_4__ {int /*<<< orphan*/ * gamma_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_free (TYPE_1__*,int /*<<< orphan*/ *) ; 

void /* PRIVATE */
png_destroy_gamma_table(png_structrp png_ptr)
{
   png_free(png_ptr, png_ptr->gamma_table);
   png_ptr->gamma_table = NULL;

#ifdef PNG_16BIT_SUPPORTED
   if (png_ptr->gamma_16_table != NULL)
   {
      int i;
      int istop = (1 << (8 - png_ptr->gamma_shift));
      for (i = 0; i < istop; i++)
      {
         png_free(png_ptr, png_ptr->gamma_16_table[i]);
      }
   png_free(png_ptr, png_ptr->gamma_16_table);
   png_ptr->gamma_16_table = NULL;
   }
#endif /* 16BIT */

#if defined(PNG_READ_BACKGROUND_SUPPORTED) || \
   defined(PNG_READ_ALPHA_MODE_SUPPORTED) || \
   defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
   png_free(png_ptr, png_ptr->gamma_from_1);
   png_ptr->gamma_from_1 = NULL;
   png_free(png_ptr, png_ptr->gamma_to_1);
   png_ptr->gamma_to_1 = NULL;

#ifdef PNG_16BIT_SUPPORTED
   if (png_ptr->gamma_16_from_1 != NULL)
   {
      int i;
      int istop = (1 << (8 - png_ptr->gamma_shift));
      for (i = 0; i < istop; i++)
      {
         png_free(png_ptr, png_ptr->gamma_16_from_1[i]);
      }
   png_free(png_ptr, png_ptr->gamma_16_from_1);
   png_ptr->gamma_16_from_1 = NULL;
   }
   if (png_ptr->gamma_16_to_1 != NULL)
   {
      int i;
      int istop = (1 << (8 - png_ptr->gamma_shift));
      for (i = 0; i < istop; i++)
      {
         png_free(png_ptr, png_ptr->gamma_16_to_1[i]);
      }
   png_free(png_ptr, png_ptr->gamma_16_to_1);
   png_ptr->gamma_16_to_1 = NULL;
   }
#endif /* 16BIT */
#endif /* READ_BACKGROUND || READ_ALPHA_MODE || RGB_TO_GRAY */
}