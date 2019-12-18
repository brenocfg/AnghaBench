#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct client_lease {TYPE_1__* options; struct client_lease* filename; struct client_lease* server_name; } ;
struct TYPE_2__ {struct client_lease* data; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct client_lease*) ; 

void
free_client_lease(struct client_lease *lease)
{
	int i;

	if (lease->server_name)
		free(lease->server_name);
	if (lease->filename)
		free(lease->filename);
	for (i = 0; i < 256; i++) {
		if (lease->options[i].len)
			free(lease->options[i].data);
	}
	free(lease);
}