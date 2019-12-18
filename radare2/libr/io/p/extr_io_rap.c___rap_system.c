#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_3__ {char* (* cb_core_cmdstr ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  (* cb_printf ) (char*,char*) ;int /*<<< orphan*/  user; } ;
typedef  int /*<<< orphan*/  RSocket ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/ * RIORAP_FD (int /*<<< orphan*/ *) ; 
 int RMT_CMD ; 
 int RMT_MAX ; 
 int RMT_REPLY ; 
 unsigned int ST32_MAX ; 
 char* calloc (int,unsigned int) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 void* r_read_at_be32 (int*,int) ; 
 int /*<<< orphan*/  r_socket_flush (int /*<<< orphan*/ *) ; 
 scalar_t__ r_socket_read (int /*<<< orphan*/ *,int*,int) ; 
 int r_socket_read_block (int /*<<< orphan*/ *,int*,unsigned int) ; 
 int /*<<< orphan*/  r_socket_write (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  r_write_be32 (int*,int) ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 
 char* stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (char*,char*) ; 
 unsigned int write (int,char*,unsigned int) ; 

__attribute__((used)) static char *__rap_system(RIO *io, RIODesc *fd, const char *command) {
	int ret, reslen = 0, cmdlen = 0;
	RSocket *s = RIORAP_FD (fd);
	unsigned int i;
	char *ptr, *res, *str;
	ut8 buf[RMT_MAX];

	buf[0] = RMT_CMD;
	i = strlen (command) + 1;
	if (i > RMT_MAX - 5) {
		eprintf ("Command too long\n");
		return NULL;
	}
	r_write_be32 (buf + 1, i);
	memcpy (buf + 5, command, i);
	(void)r_socket_write (s, buf, i+5);
	r_socket_flush (s);

	/* read reverse cmds */
	for (;;) {
		ret = r_socket_read_block (s, buf, 1);
		if (ret != 1) {
			return NULL;
		}
		/* system back in the middle */
		/* TODO: all pkt handlers should check for reverse queries */
		if (buf[0] != RMT_CMD) {
			break;
		}
		// run io->cmdstr
		// return back the string
		buf[0] |= RMT_REPLY;
		memset (buf + 1, 0, 4);
		ret = r_socket_read_block (s, buf + 1, 4);
		if (ret != 4) {
			return NULL;
		}
		cmdlen = r_read_at_be32 (buf, 1);
		if (cmdlen + 1 == 0) { // check overflow
			cmdlen = 0;
		}
		str = calloc (1, cmdlen + 1);
		ret = r_socket_read_block (s, (ut8*)str, cmdlen);
		eprintf ("RUN %d CMD(%s)\n", ret, str);
		if (str && *str) {
			res = io->cb_core_cmdstr (io->user, str);
		} else {
			res = strdup ("");
		}
		eprintf ("[%s]=>(%s)\n", str, res);
		reslen = strlen (res);
		free (str);
		r_write_be32 (buf + 1, reslen);
		memcpy (buf + 5, res, reslen);
		free (res);
		(void)r_socket_write (s, buf, reslen + 5);
		r_socket_flush (s);
	}

	// read
	ret = r_socket_read_block (s, buf + 1, 4);
	if (ret != 4) {
		return NULL;
	}
	if (buf[0] != (RMT_CMD | RMT_REPLY)) {
		eprintf ("Unexpected rap cmd reply\n");
		return NULL;
	}

	i = r_read_at_be32 (buf, 1);
	ret = 0;
	if (i > ST32_MAX) {
		eprintf ("Invalid length\n");
		return NULL;
	}
	ptr = (char *)calloc (1, i + 1);
	if (ptr) {
		int ir, tr = 0;
		do {
			ir = r_socket_read_block (s, (ut8*)ptr + tr, i - tr);
			if (ir < 1) {
				break;
			}
			tr += ir;
		} while (tr < i);
		// TODO: use io->cb_printf() with support for \x00
		ptr[i] = 0;
		if (io->cb_printf) {
			io->cb_printf ("%s", ptr);
		} else {
			if (write (1, ptr, i) != i) {
				eprintf ("Failed to write\n");
			}
		}
		free (ptr);
	}
#if DEAD_CODE
	/* Clean */
	if (ret > 0) {
		ret -= r_socket_read (s, (ut8*)buf, RMT_MAX);
	}
#endif
	return NULL;
}