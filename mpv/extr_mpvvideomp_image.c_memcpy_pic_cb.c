#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  (* memcpy_fn ) (void*,void const*,int) ;

/* Variables and functions */

__attribute__((used)) static void memcpy_pic_cb(void *dst, const void *src, int bytesPerLine, int height,
                          int dstStride, int srcStride, memcpy_fn cpy)
{
    if (bytesPerLine == dstStride && dstStride == srcStride && height) {
        if (srcStride < 0) {
            src = (uint8_t*)src + (height - 1) * srcStride;
            dst = (uint8_t*)dst + (height - 1) * dstStride;
            srcStride = -srcStride;
        }

        cpy(dst, src, srcStride * (height - 1) + bytesPerLine);
    } else {
        for (int i = 0; i < height; i++) {
            cpy(dst, src, bytesPerLine);
            src = (uint8_t*)src + srcStride;
            dst = (uint8_t*)dst + dstStride;
        }
    }
}