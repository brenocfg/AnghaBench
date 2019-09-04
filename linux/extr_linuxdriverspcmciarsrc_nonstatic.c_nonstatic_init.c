#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
struct socket_data {TYPE_3__ io_db; TYPE_2__ mem_db_valid; TYPE_1__ mem_db; } ;
struct pcmcia_socket {void* resource_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct socket_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonstatic_autoadd_resources (struct pcmcia_socket*) ; 

__attribute__((used)) static int nonstatic_init(struct pcmcia_socket *s)
{
	struct socket_data *data;

	data = kzalloc(sizeof(struct socket_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->mem_db.next = &data->mem_db;
	data->mem_db_valid.next = &data->mem_db_valid;
	data->io_db.next = &data->io_db;

	s->resource_data = (void *) data;

	nonstatic_autoadd_resources(s);

	return 0;
}