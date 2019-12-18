#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_aframe_pool {int element_size; scalar_t__ avpool; } ;
struct mp_aframe {TYPE_1__* av_frame; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int* linesize; int nb_samples; TYPE_2__** buf; scalar_t__* extended_data; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 size_t INT_MAX ; 
 size_t MPMAX (int,int) ; 
 int MP_ALIGN_UP (size_t,int) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_2__* av_buffer_pool_get (scalar_t__) ; 
 scalar_t__ av_buffer_pool_init (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_pool_uninit (scalar_t__*) ; 
 int /*<<< orphan*/  av_freep (scalar_t__**) ; 
 scalar_t__* av_mallocz_array (int,int) ; 
 int mp_aframe_get_planes (struct mp_aframe*) ; 
 size_t mp_aframe_get_sstride (struct mp_aframe*) ; 
 scalar_t__ mp_aframe_is_allocated (struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_pool_destructor ; 
 size_t ta_calc_prealloc_elems (int) ; 
 int /*<<< orphan*/  talloc_set_destructor (struct mp_aframe_pool*,int /*<<< orphan*/ ) ; 

int mp_aframe_pool_allocate(struct mp_aframe_pool *pool, struct mp_aframe *frame,
                            int samples)
{
    int planes = mp_aframe_get_planes(frame);
    size_t sstride = mp_aframe_get_sstride(frame);
    // FFmpeg hardcodes similar hidden possibly-requirements in a number of
    // places: av_frame_get_buffer(), libavcodec's get_buffer(), mem.c,
    // probably more.
    int align_samples = MP_ALIGN_UP(MPMAX(samples, 1), 32);
    int plane_size = MP_ALIGN_UP(sstride * align_samples, 64);
    int size = plane_size * planes;

    if (size <= 0 || mp_aframe_is_allocated(frame))
        return -1;

    if (!pool->avpool || size > pool->element_size) {
        size_t alloc = ta_calc_prealloc_elems(size);
        if (alloc >= INT_MAX)
            return -1;
        av_buffer_pool_uninit(&pool->avpool);
        pool->element_size = alloc;
        pool->avpool = av_buffer_pool_init(pool->element_size, NULL);
        if (!pool->avpool)
            return -1;
        talloc_set_destructor(pool, mp_aframe_pool_destructor);
    }

    // Yes, you have to do all this shit manually.
    // At least it's less stupid than av_frame_get_buffer(), which just wipes
    // the entire frame struct on error for no reason.
    AVFrame *av_frame = frame->av_frame;
    if (av_frame->extended_data != av_frame->data)
        av_freep(&av_frame->extended_data); // sigh
    av_frame->extended_data =
        av_mallocz_array(planes, sizeof(av_frame->extended_data[0]));
    if (!av_frame->extended_data)
        abort();
    av_frame->buf[0] = av_buffer_pool_get(pool->avpool);
    if (!av_frame->buf[0])
        return -1;
    av_frame->linesize[0] = samples * sstride;
    for (int n = 0; n < planes; n++)
        av_frame->extended_data[n] = av_frame->buf[0]->data + n * plane_size;
    av_frame->nb_samples = samples;

    return 0;
}