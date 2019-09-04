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
struct gb_connection {int dummy; } ;
struct gb_camera_csi_params {unsigned int clk_freq; int num_lanes; } ;
struct gb_camera_configure_streams_response {int data_rate; } ;
struct gb_camera {struct gb_connection* data_connection; TYPE_1__* connection; int /*<<< orphan*/  data_cport_id; int /*<<< orphan*/  bundle; } ;
struct ap_csi_config_request {int csi_id; int num_lanes; unsigned int csi_clk_freq; int max_pkt_size; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  csi_cfg ;
struct TYPE_2__ {int /*<<< orphan*/  hd; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GB_APB_REQUEST_CSI_TX_CONTROL ; 
 scalar_t__ GB_CAMERA_CSI_CLK_FREQ_MARGIN ; 
 int /*<<< orphan*/  GB_CAMERA_CSI_CLK_FREQ_MAX ; 
 int /*<<< orphan*/  GB_CAMERA_CSI_CLK_FREQ_MIN ; 
 int GB_CAMERA_CSI_NUM_DATA_LANES ; 
 int GB_CONNECTION_FLAG_CDSI1 ; 
 int GB_CONNECTION_FLAG_NO_FLOWCTRL ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 unsigned int clamp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gb_camera_get_max_pkt_size (struct gb_camera*,struct gb_camera_configure_streams_response*) ; 
 int gb_camera_set_power_mode (struct gb_camera*,int) ; 
 struct gb_connection* gb_connection_create_offloaded (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_camera*) ; 
 int gb_hd_output (int /*<<< orphan*/ ,struct ap_csi_config_request*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcam_err (struct gb_camera*,char*) ; 
 int /*<<< orphan*/  memset (struct ap_csi_config_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gb_camera_setup_data_connection(struct gb_camera *gcam,
		struct gb_camera_configure_streams_response *resp,
		struct gb_camera_csi_params *csi_params)
{
	struct ap_csi_config_request csi_cfg;
	struct gb_connection *conn;
	unsigned int clk_freq;
	int ret;

	/*
	 * Create the data connection between the camera module data CPort and
	 * APB CDSI1. The CDSI1 CPort ID is hardcoded by the ES2 bridge.
	 */
	conn = gb_connection_create_offloaded(gcam->bundle, gcam->data_cport_id,
					      GB_CONNECTION_FLAG_NO_FLOWCTRL |
					      GB_CONNECTION_FLAG_CDSI1);
	if (IS_ERR(conn))
		return PTR_ERR(conn);

	gcam->data_connection = conn;
	gb_connection_set_data(conn, gcam);

	ret = gb_connection_enable(conn);
	if (ret)
		goto error_conn_destroy;

	/* Set the UniPro link to high speed mode. */
	ret = gb_camera_set_power_mode(gcam, true);
	if (ret < 0)
		goto error_conn_disable;

	/*
	 * Configure the APB-A CSI-2 transmitter.
	 *
	 * Hardcode the number of lanes to 4 and compute the bus clock frequency
	 * based on the module bandwidth requirements with a safety margin.
	 */
	memset(&csi_cfg, 0, sizeof(csi_cfg));
	csi_cfg.csi_id = 1;
	csi_cfg.flags = 0;
	csi_cfg.num_lanes = GB_CAMERA_CSI_NUM_DATA_LANES;

	clk_freq = resp->data_rate / 2 / GB_CAMERA_CSI_NUM_DATA_LANES;
	clk_freq = clamp(clk_freq + GB_CAMERA_CSI_CLK_FREQ_MARGIN,
			 GB_CAMERA_CSI_CLK_FREQ_MIN,
			 GB_CAMERA_CSI_CLK_FREQ_MAX);
	csi_cfg.csi_clk_freq = clk_freq;

	ret = gb_camera_get_max_pkt_size(gcam, resp);
	if (ret < 0) {
		ret = -EIO;
		goto error_power;
	}
	csi_cfg.max_pkt_size = ret;

	ret = gb_hd_output(gcam->connection->hd, &csi_cfg,
			   sizeof(csi_cfg),
			   GB_APB_REQUEST_CSI_TX_CONTROL, false);
	if (ret < 0) {
		gcam_err(gcam, "failed to start the CSI transmitter\n");
		goto error_power;
	}

	if (csi_params) {
		csi_params->clk_freq = csi_cfg.csi_clk_freq;
		csi_params->num_lanes = csi_cfg.num_lanes;
	}

	return 0;

error_power:
	gb_camera_set_power_mode(gcam, false);
error_conn_disable:
	gb_connection_disable(gcam->data_connection);
error_conn_destroy:
	gb_connection_destroy(gcam->data_connection);
	gcam->data_connection = NULL;
	return ret;
}