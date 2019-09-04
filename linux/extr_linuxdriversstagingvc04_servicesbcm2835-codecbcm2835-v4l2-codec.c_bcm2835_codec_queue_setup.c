#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int size; unsigned int num; } ;
struct TYPE_3__ {unsigned int num; } ;
struct vchiq_mmal_port {TYPE_2__ current_buffer; TYPE_1__ minimum_buffer; } ;
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;
struct bcm2835_codec_q_data {unsigned int sizeimage; } ;
struct bcm2835_codec_ctx {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ bcm2835_codec_create_component (struct bcm2835_codec_ctx*) ; 
 struct vchiq_mmal_port* get_port_data (struct bcm2835_codec_ctx*,int /*<<< orphan*/ ) ; 
 struct bcm2835_codec_q_data* get_q_data (struct bcm2835_codec_ctx*,int /*<<< orphan*/ ) ; 
 struct bcm2835_codec_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int bcm2835_codec_queue_setup(struct vb2_queue *vq,
				     unsigned int *nbuffers,
				     unsigned int *nplanes,
				     unsigned int sizes[],
				     struct device *alloc_devs[])
{
	struct bcm2835_codec_ctx *ctx = vb2_get_drv_priv(vq);
	struct bcm2835_codec_q_data *q_data;
	struct vchiq_mmal_port *port;
	unsigned int size;

	q_data = get_q_data(ctx, vq->type);
	if (!q_data)
		return -EINVAL;

	if (!ctx->component)
		if (bcm2835_codec_create_component(ctx))
			return -EINVAL;

	port = get_port_data(ctx, vq->type);

	size = q_data->sizeimage;

	if (*nplanes)
		return sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;

	sizes[0] = size;
	port->current_buffer.size = size;

	if (*nbuffers < port->minimum_buffer.num)
		*nbuffers = port->minimum_buffer.num;
	/* Add one buffer to take an EOS */
	port->current_buffer.num = *nbuffers + 1;

	return 0;
}