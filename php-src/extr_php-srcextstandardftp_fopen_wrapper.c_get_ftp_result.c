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
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 scalar_t__ isdigit (int) ; 
 scalar_t__ php_stream_gets (int /*<<< orphan*/ *,char*,size_t) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int get_ftp_result(php_stream *stream, char *buffer, size_t buffer_size)
{
	buffer[0] = '\0'; /* in case read fails to read anything */
	while (php_stream_gets(stream, buffer, buffer_size-1) &&
		   !(isdigit((int) buffer[0]) && isdigit((int) buffer[1]) &&
			 isdigit((int) buffer[2]) && buffer[3] == ' '));
	return strtol(buffer, NULL, 10);
}