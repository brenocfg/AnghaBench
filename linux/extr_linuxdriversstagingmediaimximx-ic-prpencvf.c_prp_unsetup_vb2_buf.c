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
struct vb2_buffer {int /*<<< orphan*/  timestamp; } ;
struct prp_priv {struct imx_media_buffer** active_vb2_buf; } ;
struct TYPE_2__ {struct vb2_buffer vb2_buf; } ;
struct imx_media_buffer {TYPE_1__ vbuf; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int) ; 

__attribute__((used)) static void prp_unsetup_vb2_buf(struct prp_priv *priv,
				enum vb2_buffer_state return_status)
{
	struct imx_media_buffer *buf;
	int i;

	/* return any remaining active frames with return_status */
	for (i = 0; i < 2; i++) {
		buf = priv->active_vb2_buf[i];
		if (buf) {
			struct vb2_buffer *vb = &buf->vbuf.vb2_buf;

			vb->timestamp = ktime_get_ns();
			vb2_buffer_done(vb, return_status);
		}
	}
}