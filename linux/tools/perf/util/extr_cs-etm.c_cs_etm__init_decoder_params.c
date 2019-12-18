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
struct cs_etm_queue {int dummy; } ;
struct cs_etm_decoder_params {int operation; int formatted; int fsyncs; int hsyncs; int frame_aligned; struct cs_etm_queue* data; int /*<<< orphan*/  packet_printer; } ;
typedef  enum cs_etm_decoder_operation { ____Placeholder_cs_etm_decoder_operation } cs_etm_decoder_operation ;

/* Variables and functions */
 int CS_ETM_OPERATION_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  cs_etm__packet_dump ; 

__attribute__((used)) static int cs_etm__init_decoder_params(struct cs_etm_decoder_params *d_params,
				       struct cs_etm_queue *etmq,
				       enum cs_etm_decoder_operation mode)
{
	int ret = -EINVAL;

	if (!(mode < CS_ETM_OPERATION_MAX))
		goto out;

	d_params->packet_printer = cs_etm__packet_dump;
	d_params->operation = mode;
	d_params->data = etmq;
	d_params->formatted = true;
	d_params->fsyncs = false;
	d_params->hsyncs = false;
	d_params->frame_aligned = true;

	ret = 0;
out:
	return ret;
}