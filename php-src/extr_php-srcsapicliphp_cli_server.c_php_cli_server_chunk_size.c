#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t len; } ;
struct TYPE_6__ {size_t len; } ;
struct TYPE_8__ {TYPE_2__ immortal; TYPE_1__ heap; } ;
struct TYPE_9__ {int type; TYPE_3__ data; } ;
typedef  TYPE_4__ php_cli_server_chunk ;

/* Variables and functions */
#define  PHP_CLI_SERVER_CHUNK_HEAP 129 
#define  PHP_CLI_SERVER_CHUNK_IMMORTAL 128 

__attribute__((used)) static size_t php_cli_server_chunk_size(const php_cli_server_chunk *chunk) /* {{{ */
{
	switch (chunk->type) {
	case PHP_CLI_SERVER_CHUNK_HEAP:
		return chunk->data.heap.len;
	case PHP_CLI_SERVER_CHUNK_IMMORTAL:
		return chunk->data.immortal.len;
	}
	return 0;
}