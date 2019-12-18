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
typedef  int /*<<< orphan*/  RSocket ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/ * RIORAP_FD (int /*<<< orphan*/ *) ; 
 int RMT_MAX ; 
 int /*<<< orphan*/  RMT_WRITE ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int r_read_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_socket_flush (int /*<<< orphan*/ *) ; 
 int r_socket_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_socket_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_write_be32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __rap_write(RIO *io, RIODesc *fd, const ut8 *buf, int count) {
	RSocket *s = RIORAP_FD (fd);
	ut8 *tmp;
	int ret;

	if (count < 1) {
		return count;
	}
	// TOOD: if count > RMT_MAX iterate !
	if (count > RMT_MAX) {
		count = RMT_MAX;
	}
	if (!(tmp = (ut8 *)malloc (count + 5))) {
		eprintf ("__rap_write: malloc failed\n");
		return -1;
	}
	tmp[0] = RMT_WRITE;
	r_write_be32 (tmp + 1, count);
	memcpy (tmp + 5, buf, count);

	(void)r_socket_write (s, tmp, count + 5);
	r_socket_flush (s);
	if (r_socket_read (s, tmp, 5) != 5) { // TODO read_block?
		eprintf ("__rap_write: error\n");
		ret = -1;
	} else {
		ret = r_read_be32 (tmp + 1);
		if (!ret) {
			ret = -1;
		}
	}
	free (tmp);
	return ret;
}