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
struct TYPE_6__ {TYPE_3__* block; } ;
struct TYPE_7__ {TYPE_1__ heap; } ;
struct TYPE_8__ {int type; TYPE_2__ data; } ;
typedef  TYPE_3__ php_cli_server_chunk ;

/* Variables and functions */
#define  PHP_CLI_SERVER_CHUNK_HEAP 129 
#define  PHP_CLI_SERVER_CHUNK_IMMORTAL 128 
 int /*<<< orphan*/  pefree (TYPE_3__*,int) ; 

__attribute__((used)) static void php_cli_server_chunk_dtor(php_cli_server_chunk *chunk) /* {{{ */
{
	switch (chunk->type) {
	case PHP_CLI_SERVER_CHUNK_HEAP:
		if (chunk->data.heap.block != chunk) {
			pefree(chunk->data.heap.block, 1);
		}
		break;
	case PHP_CLI_SERVER_CHUNK_IMMORTAL:
		break;
	}
}