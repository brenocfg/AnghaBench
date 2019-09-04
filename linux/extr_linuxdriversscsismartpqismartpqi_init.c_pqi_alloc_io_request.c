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
typedef  size_t u16 ;
struct pqi_io_request {int /*<<< orphan*/  refcount; } ;
struct pqi_ctrl_info {size_t next_io_request_slot; size_t max_io_slots; struct pqi_io_request* io_request_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_reinit_io_request (struct pqi_io_request*) ; 

__attribute__((used)) static struct pqi_io_request *pqi_alloc_io_request(
	struct pqi_ctrl_info *ctrl_info)
{
	struct pqi_io_request *io_request;
	u16 i = ctrl_info->next_io_request_slot;	/* benignly racy */

	while (1) {
		io_request = &ctrl_info->io_request_pool[i];
		if (atomic_inc_return(&io_request->refcount) == 1)
			break;
		atomic_dec(&io_request->refcount);
		i = (i + 1) % ctrl_info->max_io_slots;
	}

	/* benignly racy */
	ctrl_info->next_io_request_slot = (i + 1) % ctrl_info->max_io_slots;

	pqi_reinit_io_request(io_request);

	return io_request;
}