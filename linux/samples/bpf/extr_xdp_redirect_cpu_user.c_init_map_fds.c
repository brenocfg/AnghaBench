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
struct bpf_object {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ bpf_object__find_map_fd_by_name (struct bpf_object*,char*) ; 
 scalar_t__ cpu_map_fd ; 
 scalar_t__ cpumap_enqueue_cnt_map_fd ; 
 scalar_t__ cpumap_kthread_cnt_map_fd ; 
 scalar_t__ cpus_available_map_fd ; 
 scalar_t__ cpus_count_map_fd ; 
 scalar_t__ cpus_iterator_map_fd ; 
 scalar_t__ exception_cnt_map_fd ; 
 scalar_t__ redirect_err_cnt_map_fd ; 
 scalar_t__ rx_cnt_map_fd ; 

__attribute__((used)) static int init_map_fds(struct bpf_object *obj)
{
	cpu_map_fd = bpf_object__find_map_fd_by_name(obj, "cpu_map");
	rx_cnt_map_fd = bpf_object__find_map_fd_by_name(obj, "rx_cnt");
	redirect_err_cnt_map_fd =
		bpf_object__find_map_fd_by_name(obj, "redirect_err_cnt");
	cpumap_enqueue_cnt_map_fd =
		bpf_object__find_map_fd_by_name(obj, "cpumap_enqueue_cnt");
	cpumap_kthread_cnt_map_fd =
		bpf_object__find_map_fd_by_name(obj, "cpumap_kthread_cnt");
	cpus_available_map_fd =
		bpf_object__find_map_fd_by_name(obj, "cpus_available");
	cpus_count_map_fd = bpf_object__find_map_fd_by_name(obj, "cpus_count");
	cpus_iterator_map_fd =
		bpf_object__find_map_fd_by_name(obj, "cpus_iterator");
	exception_cnt_map_fd =
		bpf_object__find_map_fd_by_name(obj, "exception_cnt");

	if (cpu_map_fd < 0 || rx_cnt_map_fd < 0 ||
	    redirect_err_cnt_map_fd < 0 || cpumap_enqueue_cnt_map_fd < 0 ||
	    cpumap_kthread_cnt_map_fd < 0 || cpus_available_map_fd < 0 ||
	    cpus_count_map_fd < 0 || cpus_iterator_map_fd < 0 ||
	    exception_cnt_map_fd < 0)
		return -ENOENT;

	return 0;
}