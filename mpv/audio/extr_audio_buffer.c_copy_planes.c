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
struct mp_audio_buffer {int num_planes; int sstride; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static void copy_planes(struct mp_audio_buffer *ab,
                        uint8_t **dst, int dst_offset,
                        uint8_t **src, int src_offset, int length)
{
    if (!length)
        return;

    for (int n = 0; n < ab->num_planes; n++) {
        memmove((char *)dst[n] + dst_offset * ab->sstride,
                (char *)src[n] + src_offset * ab->sstride,
                length * ab->sstride);
    }
}