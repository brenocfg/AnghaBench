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
struct vo {scalar_t__ hwdec_devs; struct priv* priv; } ;
struct vaapi_osd_part {int /*<<< orphan*/  image; } ;
struct priv {TYPE_1__* mpvaapi; struct vaapi_osd_part* osd_parts; int /*<<< orphan*/  pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwctx; } ;

/* Variables and functions */
 int MAX_OSD_PARTS ; 
 int /*<<< orphan*/  free_subpicture (struct priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_video_specific (struct priv*) ; 
 int /*<<< orphan*/  hwdec_devices_destroy (scalar_t__) ; 
 int /*<<< orphan*/  hwdec_devices_remove (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  vo_x11_uninit (struct vo*) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *p = vo->priv;

    free_video_specific(p);
    talloc_free(p->pool);

    for (int n = 0; n < MAX_OSD_PARTS; n++) {
        struct vaapi_osd_part *part = &p->osd_parts[n];
        free_subpicture(p, &part->image);
    }

    if (vo->hwdec_devs) {
        hwdec_devices_remove(vo->hwdec_devs, &p->mpvaapi->hwctx);
        hwdec_devices_destroy(vo->hwdec_devs);
    }

    va_destroy(p->mpvaapi);

    vo_x11_uninit(vo);
}