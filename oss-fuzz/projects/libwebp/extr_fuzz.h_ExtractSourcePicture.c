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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kImagesData ;
struct TYPE_4__ {int width; int height; int argb_stride; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 size_t Extract (size_t const,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ * const) ; 
 int WebPPictureImportRGBA (TYPE_1__* const,int /*<<< orphan*/  const* const,int) ; 
 int /*<<< orphan*/  const* kImgAlphaData ; 
 int const kImgAlphaHeight ; 
 int const kImgAlphaWidth ; 
 int /*<<< orphan*/  const* kImgGridData ; 
 int const kImgGridHeight ; 
 int const kImgGridWidth ; 
 int /*<<< orphan*/  const* kImgPeakData ; 
 int const kImgPeakHeight ; 
 int const kImgPeakWidth ; 

__attribute__((used)) static int ExtractSourcePicture(WebPPicture* const pic,
                                const uint8_t data[], size_t size,
                                uint32_t* const bit_pos) {
  if (pic == NULL) return 0;

  // Pick a source picture.
  const uint8_t* kImagesData[] = {
      kImgAlphaData,
      kImgGridData,
      kImgPeakData
  };
  const int kImagesWidth[] = {
      kImgAlphaWidth,
      kImgGridWidth,
      kImgPeakWidth
  };
  const int kImagesHeight[] = {
      kImgAlphaHeight,
      kImgGridHeight,
      kImgPeakHeight
  };
  const size_t kNbImages = sizeof(kImagesData) / sizeof(kImagesData[0]);
  const size_t image_index = Extract(kNbImages - 1, data, size, bit_pos);
  const uint8_t* const image_data = kImagesData[image_index];
  pic->width = kImagesWidth[image_index];
  pic->height = kImagesHeight[image_index];
  pic->argb_stride = pic->width * 4 * sizeof(uint8_t);

  // Read the bytes.
  return WebPPictureImportRGBA(pic, image_data, pic->argb_stride);
}