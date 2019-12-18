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
struct bpf_link {int (* destroy ) (struct bpf_link*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct bpf_link*) ; 
 int stub1 (struct bpf_link*) ; 

int bpf_link__destroy(struct bpf_link *link)
{
	int err;

	if (!link)
		return 0;

	err = link->destroy(link);
	free(link);

	return err;
}