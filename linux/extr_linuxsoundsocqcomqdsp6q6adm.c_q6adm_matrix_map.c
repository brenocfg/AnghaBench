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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct route_payload {int num_copps; int session_id; int* port_id; int* copp_idx; } ;
struct q6copp {int /*<<< orphan*/  refcount; int /*<<< orphan*/  id; } ;
struct q6adm_session_map_node_v5 {int session_id; int num_copps; } ;
struct q6adm_cmd_matrix_map_routings_v5 {int num_sessions; int /*<<< orphan*/  matrix_id; } ;
struct TYPE_4__ {int status; scalar_t__ opcode; } ;
struct q6adm {int /*<<< orphan*/  lock; TYPE_2__ result; int /*<<< orphan*/  matrix_map_wait; int /*<<< orphan*/  apr; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int pkt_size; scalar_t__ opcode; scalar_t__ token; int /*<<< orphan*/  hdr_field; } ;
struct apr_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ ADM_CMD_MATRIX_MAP_ROUTINGS_V5 ; 
 int /*<<< orphan*/  ADM_MATRIX_ID_AUDIO_RX ; 
 int /*<<< orphan*/  ADM_MATRIX_ID_AUDIO_TX ; 
#define  ADM_PATH_LIVE_REC 129 
#define  ADM_PATH_PLAYBACK 128 
 int /*<<< orphan*/  APR_HDR_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_HDR_LEN (int) ; 
 int APR_HDR_SIZE ; 
 int /*<<< orphan*/  APR_MSG_TYPE_SEQ_CMD ; 
 int /*<<< orphan*/  APR_PKT_VER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TIMEOUT_MS ; 
 int apr_send_pkt (int /*<<< orphan*/ ,struct apr_pkt*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct q6adm* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct apr_pkt*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct q6copp* q6adm_find_copp (struct q6adm*,int,int) ; 
 int /*<<< orphan*/  q6adm_free_copp ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int q6adm_matrix_map(struct device *dev, int path,
		     struct route_payload payload_map, int perf_mode)
{
	struct q6adm *adm = dev_get_drvdata(dev->parent);
	struct q6adm_cmd_matrix_map_routings_v5 *route;
	struct q6adm_session_map_node_v5 *node;
	struct apr_pkt *pkt;
	uint16_t *copps_list;
	int pkt_size, ret, i, copp_idx;
	void *matrix_map = NULL;
	struct q6copp *copp;

	/* Assumes port_ids have already been validated during adm_open */
	pkt_size = (APR_HDR_SIZE + sizeof(*route) +  sizeof(*node) +
		    (sizeof(uint32_t) * payload_map.num_copps));

	matrix_map = kzalloc(pkt_size, GFP_KERNEL);
	if (!matrix_map)
		return -ENOMEM;

	pkt = matrix_map;
	route = matrix_map + APR_HDR_SIZE;
	node = matrix_map + APR_HDR_SIZE + sizeof(*route);
	copps_list = matrix_map + APR_HDR_SIZE + sizeof(*route) + sizeof(*node);

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.token = 0;
	pkt->hdr.opcode = ADM_CMD_MATRIX_MAP_ROUTINGS_V5;
	route->num_sessions = 1;

	switch (path) {
	case ADM_PATH_PLAYBACK:
		route->matrix_id = ADM_MATRIX_ID_AUDIO_RX;
		break;
	case ADM_PATH_LIVE_REC:
		route->matrix_id = ADM_MATRIX_ID_AUDIO_TX;
		break;
	default:
		dev_err(dev, "Wrong path set[%d]\n", path);
		break;
	}

	node->session_id = payload_map.session_id;
	node->num_copps = payload_map.num_copps;

	for (i = 0; i < payload_map.num_copps; i++) {
		int port_idx = payload_map.port_id[i];

		if (port_idx < 0) {
			dev_err(dev, "Invalid port_id 0x%x\n",
				payload_map.port_id[i]);
			kfree(pkt);
			return -EINVAL;
		}
		copp_idx = payload_map.copp_idx[i];

		copp = q6adm_find_copp(adm, port_idx, copp_idx);
		if (!copp) {
			kfree(pkt);
			return -EINVAL;
		}

		copps_list[i] = copp->id;
		kref_put(&copp->refcount, q6adm_free_copp);
	}

	mutex_lock(&adm->lock);
	adm->result.status = 0;
	adm->result.opcode = 0;

	ret = apr_send_pkt(adm->apr, pkt);
	if (ret < 0) {
		dev_err(dev, "routing for stream %d failed ret %d\n",
		       payload_map.session_id, ret);
		goto fail_cmd;
	}
	ret = wait_event_timeout(adm->matrix_map_wait,
				 adm->result.opcode == pkt->hdr.opcode,
				 msecs_to_jiffies(TIMEOUT_MS));
	if (!ret) {
		dev_err(dev, "routing for stream %d failed\n",
		       payload_map.session_id);
		ret = -ETIMEDOUT;
		goto fail_cmd;
	} else if (adm->result.status > 0) {
		dev_err(dev, "DSP returned error[%d]\n",
			adm->result.status);
		ret = -EINVAL;
		goto fail_cmd;
	}

fail_cmd:
	mutex_unlock(&adm->lock);
	kfree(pkt);
	return ret;
}