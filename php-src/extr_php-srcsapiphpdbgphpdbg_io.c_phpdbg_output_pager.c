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

/* Variables and functions */
 int PHPDBG_G (int /*<<< orphan*/ ) ; 
 int PHPDBG_MAX_CMD ; 
 int /*<<< orphan*/  ZEND_STRL (char*) ; 
 int /*<<< orphan*/  lines ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  phpdbg_consume_stdin_line (char*) ; 
 scalar_t__ write (int,char const*,int) ; 
 int /*<<< orphan*/  zend_quiet_write (int,char*,...) ; 

__attribute__((used)) static int phpdbg_output_pager(int sock, const char *ptr, int len) {
	int count = 0, bytes = 0;
	const char *p = ptr, *endp = ptr + len;

	while ((p = memchr(p, '\n', endp - p))) {
		count++;
		p++;

		if (count % PHPDBG_G(lines) == 0) {
			bytes += write(sock, ptr + bytes, (p - ptr) - bytes);

			if (memchr(p, '\n', endp - p)) {
				char buf[PHPDBG_MAX_CMD];
				zend_quiet_write(sock, ZEND_STRL("\r---Type <return> to continue or q <return> to quit---"));
				phpdbg_consume_stdin_line(buf);
				if (*buf == 'q') {
					break;
				}
				zend_quiet_write(sock, "\r", 1);
			} else break;
		}
	}
	if (bytes && count % PHPDBG_G(lines) != 0) {
		bytes += write(sock, ptr + bytes, len - bytes);
	} else if (!bytes) {
		bytes += write(sock, ptr, len);
	}
	return bytes;
}