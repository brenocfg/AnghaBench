#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {int /*<<< orphan*/ * s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_str ;
typedef  int /*<<< orphan*/  php_stream ;
typedef  int /*<<< orphan*/  headerbuf ;

/* Variables and functions */
 scalar_t__ php_stream_gets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_1__*) ; 

__attribute__((used)) static zend_string *get_http_headers(php_stream *stream)
{
	smart_str tmp_response = {0};
	char headerbuf[8192];

	while (php_stream_gets(stream, headerbuf, sizeof(headerbuf))) {
		if ((headerbuf[0] == '\r' && headerbuf[1] == '\n') ||
		    (headerbuf[0] == '\n')) {
			/* empty line marks end of headers */
			smart_str_0(&tmp_response);
			return tmp_response.s;
		}

		/* add header to collection */
		smart_str_appends(&tmp_response, headerbuf);
	}

	smart_str_free(&tmp_response);
	return NULL;
}