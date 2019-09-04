#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ php_cli_server_chunk ;
struct TYPE_7__ {TYPE_1__* first; } ;
typedef  TYPE_2__ php_cli_server_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  pefree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  php_cli_server_chunk_dtor (TYPE_1__*) ; 

__attribute__((used)) static void php_cli_server_buffer_dtor(php_cli_server_buffer *buffer) /* {{{ */
{
	php_cli_server_chunk *chunk, *next;
	for (chunk = buffer->first; chunk; chunk = next) {
		next = chunk->next;
		php_cli_server_chunk_dtor(chunk);
		pefree(chunk, 1);
	}
}