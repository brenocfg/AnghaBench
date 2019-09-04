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
struct bpf_object_open_attr {char const* file; int /*<<< orphan*/  prog_type; } ;
struct bpf_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_UNSPEC ; 
 struct bpf_object* bpf_object__open_xattr (struct bpf_object_open_attr*) ; 

struct bpf_object *bpf_object__open(const char *path)
{
	struct bpf_object_open_attr attr = {
		.file		= path,
		.prog_type	= BPF_PROG_TYPE_UNSPEC,
	};

	return bpf_object__open_xattr(&attr);
}