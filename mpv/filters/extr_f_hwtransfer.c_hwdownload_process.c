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
struct mp_image {int /*<<< orphan*/  hwctx; } ;
struct mp_hwdownload {int /*<<< orphan*/  pool; } ;
struct mp_frame {scalar_t__ type; struct mp_image* data; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; struct mp_hwdownload* priv; } ;

/* Variables and functions */
 struct mp_frame MAKE_FRAME (scalar_t__,struct mp_image*) ; 
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  mp_frame_unref (struct mp_frame*) ; 
 struct mp_image* mp_image_hw_download (struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_can_transfer_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,struct mp_frame) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hwdownload_process(struct mp_filter *f)
{
    struct mp_hwdownload *d = f->priv;

    if (!mp_pin_can_transfer_data(f->ppins[1], f->ppins[0]))
        return;

    struct mp_frame frame = mp_pin_out_read(f->ppins[0]);
    if (frame.type != MP_FRAME_VIDEO)
        goto passthrough;

    struct mp_image *src = frame.data;
    if (!src->hwctx)
        goto passthrough;

    struct mp_image *dst = mp_image_hw_download(src, d->pool);
    if (!dst) {
        MP_ERR(f, "Could not copy hardware frame to CPU memory.\n");
        goto passthrough;
    }

    mp_frame_unref(&frame);
    mp_pin_in_write(f->ppins[1], MAKE_FRAME(MP_FRAME_VIDEO, dst));
    return;

passthrough:
    mp_pin_in_write(f->ppins[1], frame);
    return;
}