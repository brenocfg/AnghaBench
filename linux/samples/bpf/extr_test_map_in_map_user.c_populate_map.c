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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int A_OF_PORT_A ; 
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int H_OF_PORT_A ; 
 int H_OF_PORT_H ; 
 int PORT_A ; 
 int PORT_H ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_map_update_elem (int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_map_id (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void populate_map(uint32_t port_key, int magic_result)
{
	int ret;

	ret = bpf_map_update_elem(PORT_A, &port_key, &magic_result, BPF_ANY);
	assert(!ret);

	ret = bpf_map_update_elem(PORT_H, &port_key, &magic_result,
				  BPF_NOEXIST);
	assert(!ret);

	ret = bpf_map_update_elem(A_OF_PORT_A, &port_key, &PORT_A, BPF_ANY);
	assert(!ret);
	check_map_id(PORT_A, A_OF_PORT_A, port_key);

	ret = bpf_map_update_elem(H_OF_PORT_A, &port_key, &PORT_A, BPF_NOEXIST);
	assert(!ret);
	check_map_id(PORT_A, H_OF_PORT_A, port_key);

	ret = bpf_map_update_elem(H_OF_PORT_H, &port_key, &PORT_H, BPF_NOEXIST);
	assert(!ret);
	check_map_id(PORT_H, H_OF_PORT_H, port_key);
}