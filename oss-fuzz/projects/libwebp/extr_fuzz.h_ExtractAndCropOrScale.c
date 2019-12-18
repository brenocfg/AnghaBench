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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int const width; int const height; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int Extract (int,int /*<<< orphan*/  const*,size_t,int* const) ; 
 int WebPPictureCrop (TYPE_1__* const,int const,int const,int const,int const) ; 
 int WebPPictureRescale (TYPE_1__* const,int const,int const) ; 
 int max (int,int const) ; 

__attribute__((used)) static int ExtractAndCropOrScale(WebPPicture* const pic, const uint8_t data[],
                                 size_t size, uint32_t* const bit_pos) {
  if (pic == NULL) return 0;
  const int alter_input = Extract(1, data, size, bit_pos);
  const int crop_or_scale = Extract(1, data, size, bit_pos);
  const int width_ratio = 1 + Extract(7, data, size, bit_pos);
  const int height_ratio = 1 + Extract(7, data, size, bit_pos);
  if (alter_input) {
    if (crop_or_scale) {
      const uint32_t left_ratio = 1 + Extract(7, data, size, bit_pos);
      const uint32_t top_ratio = 1 + Extract(7, data, size, bit_pos);
      const int cropped_width = max(1, pic->width / width_ratio);
      const int cropped_height = max(1, pic->height / height_ratio);
      const int cropped_left = (pic->width - cropped_width) / left_ratio;
      const int cropped_top = (pic->height - cropped_height) / top_ratio;
      return WebPPictureCrop(pic, cropped_left, cropped_top, cropped_width,
                             cropped_height);
    } else {
      const int scaled_width = 1 + (pic->width * width_ratio) / 8;
      const int scaled_height = 1 + (pic->height * height_ratio) / 8;
      return WebPPictureRescale(pic, scaled_width, scaled_height);
    }
  }
  return 1;
}