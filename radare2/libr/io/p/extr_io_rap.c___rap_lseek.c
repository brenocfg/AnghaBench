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
typedef  int ut64 ;
typedef  int /*<<< orphan*/  RSocket ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/ * RIORAP_FD (int /*<<< orphan*/ *) ; 
 int RMT_REPLY ; 
 int RMT_SEEK ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int r_read_at_be64 (int*,int) ; 
 int /*<<< orphan*/  r_socket_flush (int /*<<< orphan*/ *) ; 
 int r_socket_read_block (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  r_socket_write (int /*<<< orphan*/ *,int**,int) ; 
 int /*<<< orphan*/  r_write_be64 (int*,int) ; 

__attribute__((used)) static ut64 __rap_lseek(RIO *io, RIODesc *fd, ut64 offset, int whence) {
	RSocket *s = RIORAP_FD (fd);
	ut8 tmp[10];
	tmp[0] = RMT_SEEK;
	tmp[1] = (ut8)whence;
	r_write_be64 (tmp + 2, offset);
	(void)r_socket_write (s, &tmp, 10);
	r_socket_flush (s);
	int ret = r_socket_read_block (s, (ut8*)&tmp, 9);
	if (ret != 9) {
		eprintf ("Truncated socket read\n");
		return -1;
	}
	if (tmp[0] != (RMT_SEEK | RMT_REPLY)) {
		// eprintf ("%d %d  - %02x %02x %02x %02x %02x %02x %02x\n",
		// ret, whence, tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], tmp[6]);
		eprintf ("Unexpected lseek reply (%02x -> %02x)\n", tmp[0], (RMT_SEEK | RMT_REPLY));
		return -1;
	}
	return r_read_at_be64 (tmp, 1);
}