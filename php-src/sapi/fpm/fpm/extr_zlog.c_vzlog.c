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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int MAX_BUF_LENGTH ; 
 int STDERR_FILENO ; 
 int ZLOG_HAVE_ERRNO ; 
 int ZLOG_LEVEL_MASK ; 
 int ZLOG_NOTICE ; 
 int ZLOG_SYSLOG ; 
 int errno ; 
 scalar_t__ external_logger ; 
 int /*<<< orphan*/  launched ; 
 int /*<<< orphan*/  php_syslog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ snprintf (char*,size_t,char*,char*,int) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/ * syslog_priorities ; 
 scalar_t__ vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_quiet_write (int,char*,size_t) ; 
 size_t zlog_buf_prefix (char const*,int,int,char*,size_t,int) ; 
 int /*<<< orphan*/  zlog_external (int,char*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int zlog_fd ; 
 int zlog_level ; 
 size_t zlog_limit ; 
 size_t zlog_truncate_buf (char*,size_t,int) ; 

void vzlog(const char *function, int line, int flags, const char *fmt, va_list args) /* {{{ */
{
	char buf[MAX_BUF_LENGTH];
	size_t buf_size = MAX_BUF_LENGTH;
	size_t len = 0;
	int truncated = 0;
	int saved_errno;

	if (external_logger) {
		zlog_external(flags, buf, buf_size, fmt, args);
	}

	if ((flags & ZLOG_LEVEL_MASK) < zlog_level) {
		return;
	}

	saved_errno = errno;
	len = zlog_buf_prefix(function, line, flags, buf, buf_size, zlog_fd == ZLOG_SYSLOG);

	if (len > buf_size - 1) {
		truncated = 1;
	} else {
		len += vsnprintf(buf + len, buf_size - len, fmt, args);
		if (len >= buf_size) {
			truncated = 1;
		}
	}

	if (!truncated) {
		if (flags & ZLOG_HAVE_ERRNO) {
			len += snprintf(buf + len, buf_size - len,
					": %s (%d)", strerror(saved_errno), saved_errno);
			if (len >= zlog_limit) {
				truncated = 1;
			}
		}
	}

	if (truncated) {
		len = zlog_truncate_buf(buf, zlog_limit < buf_size ? zlog_limit : buf_size, 1);
	}

#ifdef HAVE_SYSLOG_H
	if (zlog_fd == ZLOG_SYSLOG) {
		buf[len] = '\0';
		php_syslog(syslog_priorities[zlog_level], "%s", buf);
		buf[len++] = '\n';
	} else
#endif
	{
		buf[len++] = '\n';
		zend_quiet_write(zlog_fd > -1 ? zlog_fd : STDERR_FILENO, buf, len);
	}

	if (zlog_fd != STDERR_FILENO && zlog_fd != -1 &&
			!launched && (flags & ZLOG_LEVEL_MASK) >= ZLOG_NOTICE) {
		zend_quiet_write(STDERR_FILENO, buf, len);
	}
}