#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* p; size_t len; TYPE_3__* block; } ;
struct TYPE_7__ {TYPE_1__ heap; } ;
struct TYPE_8__ {TYPE_2__ data; int /*<<< orphan*/ * next; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ php_cli_server_chunk ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_CLI_SERVER_CHUNK_HEAP ; 
 TYPE_3__* pemalloc (int,int) ; 

__attribute__((used)) static php_cli_server_chunk *php_cli_server_chunk_heap_new_self_contained(size_t len) /* {{{ */
{
	php_cli_server_chunk *chunk = pemalloc(sizeof(php_cli_server_chunk) + len, 1);

	chunk->type = PHP_CLI_SERVER_CHUNK_HEAP;
	chunk->next = NULL;
	chunk->data.heap.block = chunk;
	chunk->data.heap.p = (char *)(chunk + 1);
	chunk->data.heap.len = len;
	return chunk;
}