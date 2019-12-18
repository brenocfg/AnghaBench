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
typedef  size_t uint32_t ;
struct xvctx {size_t formats; TYPE_1__* fo; } ;
struct vo {struct xvctx* priv; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int find_xv_format (int) ; 

__attribute__((used)) static int query_format(struct vo *vo, int format)
{
    struct xvctx *ctx = vo->priv;
    uint32_t i;

    int fourcc = find_xv_format(format);
    if (fourcc) {
        for (i = 0; i < ctx->formats; i++) {
            if (ctx->fo[i].id == fourcc)
                return 1;
        }
    }
    return 0;
}