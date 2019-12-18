#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vo {struct priv* priv; } ;
struct priv {TYPE_1__* next_image; } ;
struct TYPE_2__ {scalar_t__* planes; } ;
typedef  int /*<<< orphan*/  AVMediaCodecBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  av_mediacodec_release_buffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_image_unrefp (TYPE_1__**) ; 

__attribute__((used)) static void flip_page(struct vo *vo)
{
    struct priv *p = vo->priv;
    if (!p->next_image)
        return;

    AVMediaCodecBuffer *buffer = (AVMediaCodecBuffer *)p->next_image->planes[3];
    av_mediacodec_release_buffer(buffer, 1);
    mp_image_unrefp(&p->next_image);
}