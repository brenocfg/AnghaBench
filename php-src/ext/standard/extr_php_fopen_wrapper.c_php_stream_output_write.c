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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  PHPWRITE (char const*,size_t) ; 

__attribute__((used)) static ssize_t php_stream_output_write(php_stream *stream, const char *buf, size_t count) /* {{{ */
{
	PHPWRITE(buf, count);
	return count;
}