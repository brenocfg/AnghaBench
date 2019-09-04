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
struct priv {int /*<<< orphan*/  vscore; TYPE_1__* vsapi; } ;
struct mp_image_params {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  imgfmt; } ;
typedef  int /*<<< orphan*/  VSFrameRef ;
typedef  int /*<<< orphan*/  VSFormat ;
struct TYPE_2__ {int /*<<< orphan*/ * (* newVideoFrame ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* getFormatPreset ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mp_to_vs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VSFrameRef *alloc_vs_frame(struct priv *p, struct mp_image_params *fmt)
{
    const VSFormat *vsfmt =
        p->vsapi->getFormatPreset(mp_to_vs(fmt->imgfmt), p->vscore);
    return p->vsapi->newVideoFrame(vsfmt, fmt->w, fmt->h, NULL, p->vscore);
}