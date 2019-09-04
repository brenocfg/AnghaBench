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
typedef  int /*<<< orphan*/  php_stream_wrapper ;
typedef  int /*<<< orphan*/  php_stream_statbuf ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */

__attribute__((used)) static int php_stream_ftp_stream_stat(php_stream_wrapper *wrapper, php_stream *stream, php_stream_statbuf *ssb)
{
	/* For now, we return with a failure code to prevent the underlying
	 * file's details from being used instead. */
	return -1;
}