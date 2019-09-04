#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct priv {TYPE_1__* vsapi; } ;
struct mp_image {int num_planes; int /*<<< orphan*/ * stride; int /*<<< orphan*/ ** planes; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  VSFrameRef ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ VSFormat ;
struct TYPE_4__ {int /*<<< orphan*/  (* getStride ) (int /*<<< orphan*/  const*,int) ;scalar_t__ (* getReadPtr ) (int /*<<< orphan*/  const*,int) ;int /*<<< orphan*/ * (* getWritePtr ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* getFrameHeight ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* getFrameWidth ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;TYPE_2__* (* getFrameFormat ) (int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mp_from_vs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int /*<<< orphan*/ ) ; 
 TYPE_2__* stub1 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub4 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub5 (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static struct mp_image map_vs_frame(struct priv *p, const VSFrameRef *ref,
                                    bool w)
{
    const VSFormat *fmt = p->vsapi->getFrameFormat(ref);

    struct mp_image img = {0};
    mp_image_setfmt(&img, mp_from_vs(fmt->id));
    mp_image_set_size(&img, p->vsapi->getFrameWidth(ref, 0),
                            p->vsapi->getFrameHeight(ref, 0));

    for (int n = 0; n < img.num_planes; n++) {
        if (w) {
            img.planes[n] = p->vsapi->getWritePtr((VSFrameRef *)ref, n);
        } else {
            img.planes[n] = (uint8_t *)p->vsapi->getReadPtr(ref, n);
        }
        img.stride[n] = p->vsapi->getStride(ref, n);
    }

    return img;
}