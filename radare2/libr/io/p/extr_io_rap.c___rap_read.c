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
typedef  int /*<<< orphan*/  RSocket ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/ * RIORAP_FD (int /*<<< orphan*/ *) ; 
 int RMT_MAX ; 
 int RMT_READ ; 
 int RMT_REPLY ; 
 int /*<<< orphan*/  eprintf (char*,int,int,...) ; 
 int r_read_at_be32 (int*,int) ; 
 int /*<<< orphan*/  r_socket_flush (int /*<<< orphan*/ *) ; 
 int r_socket_read_block (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  r_socket_write (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  r_write_be32 (int*,int) ; 

__attribute__((used)) static int __rap_read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	RSocket *s = RIORAP_FD (fd);
	int ret, i = (int)count;
	ut8 tmp[5];

	// XXX. if count is > RMT_MAX, just perform multiple queries
	if (count > RMT_MAX) {
		count = RMT_MAX;
	}
	// send
	tmp[0] = RMT_READ;
	r_write_be32 (tmp + 1, count);
	(void)r_socket_write (s, tmp, 5);
	r_socket_flush (s);
	// recv
	ret = r_socket_read_block (s, tmp, 5);
	if (ret != 5 || tmp[0] != (RMT_READ | RMT_REPLY)) {
		eprintf ("__rap_read: Unexpected rap read reply "
			"(%d=0x%02x) expected (%d=0x%02x)\n",
			ret, tmp[0], 2, (RMT_READ | RMT_REPLY));
		return -1;
	}
	i = r_read_at_be32 (tmp, 1);
	if (i > count) {
		eprintf ("__rap_read: Unexpected data size %d vs %d\n", i, count);
		return -1;
	}
	r_socket_read_block (s, buf, i);
	return count;
}