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
struct gb_operation {struct gb_message* request; int /*<<< orphan*/  type; int /*<<< orphan*/  connection; } ;
struct gb_message {int payload_size; struct gb_camera_metadata_request* payload; } ;
struct gb_camera_metadata_request {int /*<<< orphan*/  stream; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  request_id; } ;
struct gb_camera {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GB_CAMERA_TYPE_METADATA ; 
 struct gb_camera* gb_connection_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcam_dbg (struct gb_camera*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcam_err (struct gb_camera*,char*,int,...) ; 

__attribute__((used)) static int gb_camera_request_handler(struct gb_operation *op)
{
	struct gb_camera *gcam = gb_connection_get_data(op->connection);
	struct gb_camera_metadata_request *payload;
	struct gb_message *request;

	if (op->type != GB_CAMERA_TYPE_METADATA) {
		gcam_err(gcam, "Unsupported unsolicited event: %u\n", op->type);
		return -EINVAL;
	}

	request = op->request;

	if (request->payload_size < sizeof(*payload)) {
		gcam_err(gcam, "Wrong event size received (%zu < %zu)\n",
			 request->payload_size, sizeof(*payload));
		return -EINVAL;
	}

	payload = request->payload;

	gcam_dbg(gcam, "received metadata for request %u, frame %u, stream %u\n",
		 payload->request_id, payload->frame_number, payload->stream);

	return 0;
}