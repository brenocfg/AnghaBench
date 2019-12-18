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
struct TYPE_4__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
typedef  int /*<<< orphan*/  phar_entry_data ;

/* Variables and functions */
 int /*<<< orphan*/  phar_entry_delref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phar_stream_flush (TYPE_1__*) ; 

__attribute__((used)) static int phar_stream_close(php_stream *stream, int close_handle) /* {{{ */
{
	/* for some reasons phar needs to be flushed even if there is no write going on */
	phar_stream_flush(stream);

	phar_entry_delref((phar_entry_data *)stream->abstract);

	return 0;
}