#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t st_size; } ;
struct TYPE_9__ {TYPE_2__ sb; } ;
typedef  TYPE_3__ php_stream_statbuf ;
struct TYPE_7__ {scalar_t__ head; } ;
struct TYPE_10__ {TYPE_1__ readfilters; } ;
typedef  TYPE_4__ php_stream ;

/* Variables and functions */
 scalar_t__ php_stream_stat (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static size_t php_zend_stream_fsizer(void *handle) /* {{{ */
{
	php_stream *stream = handle;
	php_stream_statbuf ssb;

	/* File size reported by stat() may be inaccurate if stream filters are used.
	 * TODO: Should stat() be generally disabled if filters are used? */
	if (stream->readfilters.head) {
		return 0;
	}

	if (php_stream_stat(stream, &ssb) == 0) {
		return ssb.sb.st_size;
	}
	return 0;
}