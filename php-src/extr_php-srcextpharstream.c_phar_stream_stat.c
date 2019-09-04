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
typedef  int /*<<< orphan*/  php_stream_statbuf ;
struct TYPE_4__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
struct TYPE_5__ {int /*<<< orphan*/  internal_file; int /*<<< orphan*/  phar; } ;
typedef  TYPE_2__ phar_entry_data ;

/* Variables and functions */
 int /*<<< orphan*/  phar_dostat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phar_stream_stat(php_stream *stream, php_stream_statbuf *ssb) /* {{{ */
{
	phar_entry_data *data = (phar_entry_data *)stream->abstract;

	/* If ssb is NULL then someone is misbehaving */
	if (!ssb) {
		return -1;
	}

	phar_dostat(data->phar, data->internal_file, ssb, 0);
	return 0;
}