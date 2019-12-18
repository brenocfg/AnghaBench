#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct xvctx {int /*<<< orphan*/  xv_port; } ;
struct vo {TYPE_1__* x11; struct xvctx* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ XvEncodingInfo ;
struct TYPE_5__ {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XvFreeEncodingInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  XvQueryEncodings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,TYPE_2__**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void xv_get_max_img_dim(struct vo *vo, uint32_t *width, uint32_t *height)
{
    struct xvctx *ctx = vo->priv;
    XvEncodingInfo *encodings;
    unsigned int num_encodings, idx;

    XvQueryEncodings(vo->x11->display, ctx->xv_port, &num_encodings, &encodings);

    if (encodings) {
        for (idx = 0; idx < num_encodings; ++idx) {
            if (strcmp(encodings[idx].name, "XV_IMAGE") == 0) {
                *width  = encodings[idx].width;
                *height = encodings[idx].height;
                break;
            }
        }
    }

    MP_VERBOSE(vo, "Maximum source image dimensions: %ux%u\n", *width, *height);

    XvFreeEncodingInfo(encodings);
}