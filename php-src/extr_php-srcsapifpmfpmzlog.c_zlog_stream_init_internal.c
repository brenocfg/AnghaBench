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
struct zlog_stream {int flags; int use_syslog; int use_fd; int use_buffer; size_t buf_init_size; int use_stderr; int prefix_buffer; int fd; } ;

/* Variables and functions */
 int STDERR_FILENO ; 
 int STDOUT_FILENO ; 
 int ZLOG_LEVEL_MASK ; 
 int ZLOG_NOTICE ; 
 int ZLOG_SYSLOG ; 
 int /*<<< orphan*/ * external_logger ; 
 int /*<<< orphan*/  launched ; 
 int /*<<< orphan*/  memset (struct zlog_stream*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zlog_buffering ; 
 int zlog_fd ; 
 int zlog_level ; 

__attribute__((used)) static inline void zlog_stream_init_internal(
		struct zlog_stream *stream, int flags, size_t capacity, int fd) /* {{{ */
{
	if (fd == 0) {
		fd = zlog_fd;
	}

	memset(stream, 0, sizeof(struct zlog_stream));
	stream->flags = flags;
	stream->use_syslog = fd == ZLOG_SYSLOG;
	stream->use_fd = fd > 0;
	stream->use_buffer = zlog_buffering || external_logger != NULL || stream->use_syslog;
	stream->buf_init_size = capacity;
	stream->use_stderr = fd < 0 ||
			(
				fd != STDERR_FILENO && fd != STDOUT_FILENO && !launched &&
				(flags & ZLOG_LEVEL_MASK) >= ZLOG_NOTICE
			);
	stream->prefix_buffer = (flags & ZLOG_LEVEL_MASK) >= zlog_level &&
			(stream->use_fd || stream->use_stderr || stream->use_syslog);
	stream->fd = fd > -1 ? fd : STDERR_FILENO;
}