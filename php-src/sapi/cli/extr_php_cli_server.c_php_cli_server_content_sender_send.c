#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  php_socket_t ;
struct TYPE_11__ {int /*<<< orphan*/ * last; TYPE_6__* first; } ;
struct TYPE_14__ {TYPE_2__ buffer; } ;
typedef  TYPE_5__ php_cli_server_content_sender ;
struct TYPE_12__ {size_t p; int len; } ;
struct TYPE_10__ {size_t p; int len; } ;
struct TYPE_13__ {TYPE_3__ immortal; TYPE_1__ heap; } ;
struct TYPE_15__ {int type; TYPE_4__ data; struct TYPE_15__* next; } ;
typedef  TYPE_6__ php_cli_server_chunk ;

/* Variables and functions */
#define  PHP_CLI_SERVER_CHUNK_HEAP 129 
#define  PHP_CLI_SERVER_CHUNK_IMMORTAL 128 
 int /*<<< orphan*/  pefree (TYPE_6__*,int) ; 
 int /*<<< orphan*/  php_cli_server_chunk_dtor (TYPE_6__*) ; 
 int php_socket_errno () ; 
 size_t send (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_cli_server_content_sender_send(php_cli_server_content_sender *sender, php_socket_t fd, size_t *nbytes_sent_total) /* {{{ */
{
	php_cli_server_chunk *chunk, *next;
	size_t _nbytes_sent_total = 0;

	for (chunk = sender->buffer.first; chunk; chunk = next) {
#ifdef PHP_WIN32
		int nbytes_sent;
#else
		ssize_t nbytes_sent;
#endif
		next = chunk->next;

		switch (chunk->type) {
		case PHP_CLI_SERVER_CHUNK_HEAP:
#ifdef PHP_WIN32
			nbytes_sent = send(fd, chunk->data.heap.p, (int)chunk->data.heap.len, 0);
#else
			nbytes_sent = send(fd, chunk->data.heap.p, chunk->data.heap.len, 0);
#endif
			if (nbytes_sent < 0) {
				*nbytes_sent_total = _nbytes_sent_total;
				return php_socket_errno();
#ifdef PHP_WIN32
			} else if (nbytes_sent == chunk->data.heap.len) {
#else
			} else if (nbytes_sent == (ssize_t)chunk->data.heap.len) {
#endif
				php_cli_server_chunk_dtor(chunk);
				pefree(chunk, 1);
				sender->buffer.first = next;
				if (!next) {
					sender->buffer.last = NULL;
				}
			} else {
				chunk->data.heap.p += nbytes_sent;
				chunk->data.heap.len -= nbytes_sent;
			}
			_nbytes_sent_total += nbytes_sent;
			break;

		case PHP_CLI_SERVER_CHUNK_IMMORTAL:
#ifdef PHP_WIN32
			nbytes_sent = send(fd, chunk->data.immortal.p, (int)chunk->data.immortal.len, 0);
#else
			nbytes_sent = send(fd, chunk->data.immortal.p, chunk->data.immortal.len, 0);
#endif
			if (nbytes_sent < 0) {
				*nbytes_sent_total = _nbytes_sent_total;
				return php_socket_errno();
#ifdef PHP_WIN32
			} else if (nbytes_sent == chunk->data.immortal.len) {
#else
			} else if (nbytes_sent == (ssize_t)chunk->data.immortal.len) {
#endif
				php_cli_server_chunk_dtor(chunk);
				pefree(chunk, 1);
				sender->buffer.first = next;
				if (!next) {
					sender->buffer.last = NULL;
				}
			} else {
				chunk->data.immortal.p += nbytes_sent;
				chunk->data.immortal.len -= nbytes_sent;
			}
			_nbytes_sent_total += nbytes_sent;
			break;
		}
	}
	*nbytes_sent_total = _nbytes_sent_total;
	return 0;
}