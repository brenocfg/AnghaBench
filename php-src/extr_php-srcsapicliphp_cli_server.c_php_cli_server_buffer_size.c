#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ php_cli_server_chunk ;
struct TYPE_6__ {TYPE_1__* first; } ;
typedef  TYPE_2__ php_cli_server_buffer ;

/* Variables and functions */
 scalar_t__ php_cli_server_chunk_size (TYPE_1__*) ; 

__attribute__((used)) static size_t php_cli_server_buffer_size(const php_cli_server_buffer *buffer) /* {{{ */
{
	php_cli_server_chunk *chunk;
	size_t retval = 0;
	for (chunk = buffer->first; chunk; chunk = chunk->next) {
		retval += php_cli_server_chunk_size(chunk);
	}
	return retval;
}