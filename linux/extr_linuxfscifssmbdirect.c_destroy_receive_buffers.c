#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smbd_response {int dummy; } ;
struct smbd_connection {int /*<<< orphan*/  response_mempool; } ;

/* Variables and functions */
 struct smbd_response* get_empty_queue_buffer (struct smbd_connection*) ; 
 struct smbd_response* get_receive_buffer (struct smbd_connection*) ; 
 int /*<<< orphan*/  mempool_free (struct smbd_response*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_receive_buffers(struct smbd_connection *info)
{
	struct smbd_response *response;

	while ((response = get_receive_buffer(info)))
		mempool_free(response, info->response_mempool);

	while ((response = get_empty_queue_buffer(info)))
		mempool_free(response, info->response_mempool);
}