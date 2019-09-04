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
typedef  int /*<<< orphan*/  const ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
struct gport {scalar_t__ (* get_reply ) (struct gport*,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ;scalar_t__ (* send_request ) (struct gport*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* frame ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  max_rx_size; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  const GPROBE_RAM_READ_2 ; 
 int /*<<< orphan*/  R_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_buf_append_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_write_be32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct gport*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (struct gport*,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gprobe_read(struct gport *port, ut32 addr, ut8 *buf, ut32 count) {
	RBuffer *request = r_buf_new ();
	RBuffer *reply = r_buf_new ();
	const ut8 cmd = GPROBE_RAM_READ_2;
	ut8 addr_be[4];
	ut8 count_be[4];
	int res;

	if (!request || !reply) {
		r_buf_free (request);
		r_buf_free (reply);
		return -1;
	}

	count = R_MIN (port->max_rx_size, count);

	r_write_be32 (addr_be, addr);
	r_write_be32 (count_be, count);

	r_buf_append_bytes (request, &cmd, 1);
	r_buf_append_bytes (request, addr_be, 4);
	r_buf_append_bytes (request, count_be, 4);

	port->frame (request);

	if (port->send_request (port, request)) {
		goto fail;
	}

	if (port->get_reply (port, cmd, reply)) {
		goto fail;
	}

	res = r_buf_read_at (reply, 0, buf, r_buf_size (reply));

	r_buf_free (request);
	r_buf_free (reply);

	return res;

fail:
	r_buf_free (request);
	r_buf_free (reply);
	return -1;
}