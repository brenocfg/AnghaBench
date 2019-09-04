#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t st_size; } ;
struct TYPE_5__ {TYPE_1__ sb; } ;
typedef  TYPE_2__ php_stream_statbuf ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 scalar_t__ php_stream_stat (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static size_t php_zend_stream_fsizer(void *handle) /* {{{ */
{
	php_stream_statbuf  ssb;
	if (php_stream_stat((php_stream*)handle, &ssb) == 0) {
		return ssb.sb.st_size;
	}
	return 0;
}