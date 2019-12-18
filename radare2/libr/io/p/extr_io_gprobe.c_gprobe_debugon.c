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
typedef  int /*<<< orphan*/  ut8 ;
struct gport {scalar_t__ (* get_reply ) (struct gport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* send_request ) (struct gport*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* frame ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  GPROBE_ACK ; 
 int /*<<< orphan*/  GPROBE_DEBUGON ; 
 int /*<<< orphan*/  r_buf_append_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct gport*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (struct gport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gprobe_debugon (struct gport *port) {
	if (!port) {
		return -1;
	}
	RBuffer *request = r_buf_new ();
	RBuffer *reply = r_buf_new ();
	const ut8 cmd = GPROBE_DEBUGON;

	if (!request || !reply) {
		goto fail;
	}
	r_buf_append_bytes (request, &cmd, 1);

	port->frame (request);

	if (port->send_request (port, request)) {
		goto fail;
	}

	if (port->get_reply (port, GPROBE_ACK, reply)) {
		goto fail;
	}

	r_buf_free (request);
	r_buf_free (reply);

	return 0;

fail:
	r_buf_free (request);
	r_buf_free (reply);
	return -1;
}