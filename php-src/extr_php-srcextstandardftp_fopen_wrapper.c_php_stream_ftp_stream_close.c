#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream_wrapper ;
struct TYPE_6__ {struct TYPE_6__* wrapperthis; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ php_stream ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  E_WARNING ; 
 int GET_FTP_RESULT (TYPE_1__*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  php_stream_close (TYPE_1__*) ; 
 int /*<<< orphan*/  php_stream_write_string (TYPE_1__*,char*) ; 
 scalar_t__ strpbrk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int php_stream_ftp_stream_close(php_stream_wrapper *wrapper, php_stream *stream)
{
	php_stream *controlstream = stream->wrapperthis;
	int ret = 0;

	if (controlstream) {
		if (strpbrk(stream->mode, "wa+")) {
			char tmp_line[512];
			int result;

			/* For write modes close data stream first to signal EOF to server */
			result = GET_FTP_RESULT(controlstream);
			if (result != 226 && result != 250) {
				php_error_docref(NULL, E_WARNING, "FTP server error %d:%s", result, tmp_line);
				ret = EOF;
			}
		}

		php_stream_write_string(controlstream, "QUIT\r\n");
		php_stream_close(controlstream);
		stream->wrapperthis = NULL;
	}

	return ret;
}