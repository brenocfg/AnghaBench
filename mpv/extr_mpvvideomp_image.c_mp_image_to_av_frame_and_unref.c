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
struct AVFrame {int dummy; } ;
typedef  struct AVFrame AVFrame ;

/* Variables and functions */
 struct AVFrame* mp_image_to_av_frame (struct mp_image*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

struct AVFrame *mp_image_to_av_frame_and_unref(struct mp_image *img)
{
    AVFrame *frame = mp_image_to_av_frame(img);
    talloc_free(img);
    return frame;
}