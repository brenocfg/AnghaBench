#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream_filter ;
struct TYPE_4__ {int /*<<< orphan*/  writefilters; int /*<<< orphan*/  readfilters; } ;
typedef  TYPE_1__ php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  php_stream_filter_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_stream_filter_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_is_persistent (TYPE_1__*) ; 
 char* php_strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  php_url_decode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void php_stream_apply_filter_list(php_stream *stream, char *filterlist, int read_chain, int write_chain) /* {{{ */
{
	char *p, *token = NULL;
	php_stream_filter *temp_filter;

	p = php_strtok_r(filterlist, "|", &token);
	while (p) {
		php_url_decode(p, strlen(p));
		if (read_chain) {
			if ((temp_filter = php_stream_filter_create(p, NULL, php_stream_is_persistent(stream)))) {
				php_stream_filter_append(&stream->readfilters, temp_filter);
			} else {
				php_error_docref(NULL, E_WARNING, "Unable to create filter (%s)", p);
			}
		}
		if (write_chain) {
			if ((temp_filter = php_stream_filter_create(p, NULL, php_stream_is_persistent(stream)))) {
				php_stream_filter_append(&stream->writefilters, temp_filter);
			} else {
				php_error_docref(NULL, E_WARNING, "Unable to create filter (%s)", p);
			}
		}
		p = php_strtok_r(NULL, "|", &token);
	}
}