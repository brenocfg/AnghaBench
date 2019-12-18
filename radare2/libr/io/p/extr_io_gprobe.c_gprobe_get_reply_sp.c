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
typedef  int ut8 ;
struct gport {int dummy; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int gprobe_checksum (int*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  r_buf_append_bytes (int /*<<< orphan*/ *,int*,int) ; 
 int sp_blocking_read (struct gport*,int*,int,int) ; 

__attribute__((used)) static int gprobe_get_reply_sp(struct gport *port, ut8 cmd, RBuffer *reply) {
	ut8 buf[256];
	int count = sp_blocking_read (port, buf, 2, 50);

	if (count < 2) {
		return -1;
	}

	if (cmd != buf[1]) {
		return -1;
	}

	if (!(buf[0] - 2)) {
		return 0;
	}

	count = sp_blocking_read (port, buf + 2, buf[0] - 2, 50) + 2;

	if (count != buf[0]) {
		return -1;
	}

/* checksumming answers does not work reliably */
#if 0
	if (gprobe_checksum(buf, count - 1) != buf[count - 1]) {
		printf("### CHECKSUM FAILED\n");
	}
#endif

	r_buf_append_bytes (reply, buf + 2, count - 3);

	return 0;
}