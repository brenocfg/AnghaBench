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
struct bpf_link_fd {int /*<<< orphan*/  fd; } ;
struct bpf_link {int dummy; } ;

/* Variables and functions */
 int close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_link__destroy_fd(struct bpf_link *link)
{
	struct bpf_link_fd *l = (void *)link;

	return close(l->fd);
}