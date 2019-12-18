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

/* Variables and functions */
 int ENOENT ; 
 void* ERR_PTR (int) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int bpf_map_delete_elem (int,int*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  is_stopped () ; 
 int /*<<< orphan*/  notify_thread_err () ; 
 int /*<<< orphan*/  sk_storage_map ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void *delete_thread(void *arg)
{
	int map_fd = READ_ONCE(sk_storage_map);
	int sk_fd = *(int *)arg;
	int err = 0; /* Suppress compiler false alarm */

	while (!is_stopped()) {
		err = bpf_map_delete_elem(map_fd, &sk_fd);
		if (err && errno != ENOENT) {
			err = -errno;
			fprintf(stderr, "bpf_map_delete_elem: %d %d\n",
				err, errno);
			break;
		}
	}

	if (!is_stopped()) {
		notify_thread_err();
		return ERR_PTR(err);
	}

	return NULL;
}