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
struct v4l2_ctrl_handler {int error; } ;
struct imx_media_fim {void** icap_ctrl; void** ctrl; struct v4l2_ctrl_handler ctrl_handler; } ;

/* Variables and functions */
 int FIM_NUM_CONTROLS ; 
 int FIM_NUM_ICAP_CONTROLS ; 
 int /*<<< orphan*/ * fim_ctrl ; 
 int /*<<< orphan*/ * fim_icap_ctrl ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 void* v4l2_ctrl_new_custom (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_fim_controls(struct imx_media_fim *fim)
{
	struct v4l2_ctrl_handler *hdlr = &fim->ctrl_handler;
	int i, ret;

	v4l2_ctrl_handler_init(hdlr, FIM_NUM_CONTROLS + FIM_NUM_ICAP_CONTROLS);

	for (i = 0; i < FIM_NUM_CONTROLS; i++)
		fim->ctrl[i] = v4l2_ctrl_new_custom(hdlr,
						    &fim_ctrl[i],
						    NULL);
	for (i = 0; i < FIM_NUM_ICAP_CONTROLS; i++)
		fim->icap_ctrl[i] = v4l2_ctrl_new_custom(hdlr,
							 &fim_icap_ctrl[i],
							 NULL);
	if (hdlr->error) {
		ret = hdlr->error;
		goto err_free;
	}

	v4l2_ctrl_cluster(FIM_NUM_CONTROLS, fim->ctrl);
	v4l2_ctrl_cluster(FIM_NUM_ICAP_CONTROLS, fim->icap_ctrl);

	return 0;
err_free:
	v4l2_ctrl_handler_free(hdlr);
	return ret;
}