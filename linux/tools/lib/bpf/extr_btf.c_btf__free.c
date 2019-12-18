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
struct btf {int fd; struct btf* types; struct btf* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct btf*) ; 

void btf__free(struct btf *btf)
{
	if (!btf)
		return;

	if (btf->fd != -1)
		close(btf->fd);

	free(btf->data);
	free(btf->types);
	free(btf);
}