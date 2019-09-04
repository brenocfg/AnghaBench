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
struct mp_image {int dummy; } ;
struct gl_video {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_video_check_format (struct gl_video*,int) ; 
 void* gl_video_dr_alloc_buffer (struct gl_video*,int) ; 
 int /*<<< orphan*/  gl_video_dr_free_buffer (struct gl_video*,void*) ; 
 struct mp_image* mp_image_from_buffer (int,int,int,int,void*,int,struct gl_video*,int /*<<< orphan*/  (*) (struct gl_video*,void*)) ; 
 int mp_image_get_alloc_size (int,int,int,int) ; 

struct mp_image *gl_video_get_image(struct gl_video *p, int imgfmt, int w, int h,
                                    int stride_align)
{
    if (!gl_video_check_format(p, imgfmt))
        return NULL;

    int size = mp_image_get_alloc_size(imgfmt, w, h, stride_align);
    if (size < 0)
        return NULL;

    int alloc_size = size + stride_align;
    void *ptr = gl_video_dr_alloc_buffer(p, alloc_size);
    if (!ptr)
        return NULL;

    // (we expect vo.c to proxy the free callback, so it happens in the same
    // thread it was allocated in, removing the need for synchronization)
    struct mp_image *res = mp_image_from_buffer(imgfmt, w, h, stride_align,
                                                ptr, alloc_size, p,
                                                gl_video_dr_free_buffer);
    if (!res)
        gl_video_dr_free_buffer(p, ptr);
    return res;
}