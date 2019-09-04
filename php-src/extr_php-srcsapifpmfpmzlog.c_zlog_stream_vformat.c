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
struct zlog_stream {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog_stream_str (struct zlog_stream*,char*,size_t) ; 

ssize_t zlog_stream_vformat(struct zlog_stream *stream, const char *fmt, va_list args) /* {{{ */
{
	char sbuf[1024];
	size_t len;

	len = vsnprintf(sbuf, 1024, fmt, args);

	return zlog_stream_str(stream, sbuf, len);
}