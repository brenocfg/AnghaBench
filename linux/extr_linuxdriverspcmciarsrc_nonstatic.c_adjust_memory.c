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
struct socket_data {int /*<<< orphan*/  mem_db; } ;
struct pcmcia_socket {struct socket_data* resource_data; } ;

/* Variables and functions */
#define  ADD_MANAGED_RESOURCE 129 
 int EINVAL ; 
#define  REMOVE_MANAGED_RESOURCE 128 
 int add_interval (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  do_mem_probe (struct pcmcia_socket*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sub_interval (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static int adjust_memory(struct pcmcia_socket *s, unsigned int action, unsigned long start, unsigned long end)
{
	struct socket_data *data = s->resource_data;
	unsigned long size = end - start + 1;
	int ret = 0;

	if (end < start)
		return -EINVAL;

	switch (action) {
	case ADD_MANAGED_RESOURCE:
		ret = add_interval(&data->mem_db, start, size);
		if (!ret)
			do_mem_probe(s, start, size, NULL, NULL);
		break;
	case REMOVE_MANAGED_RESOURCE:
		ret = sub_interval(&data->mem_db, start, size);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}