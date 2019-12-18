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
struct lavc_conv {int /*<<< orphan*/  avctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  avcodec_flush_buffers (int /*<<< orphan*/ ) ; 

void lavc_conv_reset(struct lavc_conv *priv)
{
    avcodec_flush_buffers(priv->avctx);
}