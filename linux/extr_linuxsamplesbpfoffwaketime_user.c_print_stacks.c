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
struct key_t {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 scalar_t__ bpf_map_get_next_key (int,struct key_t*,struct key_t*) ; 
 int /*<<< orphan*/  bpf_map_lookup_elem (int,struct key_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_stack (struct key_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_stacks(int fd)
{
	struct key_t key = {}, next_key;
	__u64 value;

	while (bpf_map_get_next_key(fd, &key, &next_key) == 0) {
		bpf_map_lookup_elem(fd, &next_key, &value);
		print_stack(&next_key, value);
		key = next_key;
	}
}