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
struct bpf_object_open_attr {int dummy; } ;
struct bpf_object {int dummy; } ;

/* Variables and functions */
 struct bpf_object* __bpf_object__open_xattr (struct bpf_object_open_attr*,int /*<<< orphan*/ ) ; 

struct bpf_object *bpf_object__open_xattr(struct bpf_object_open_attr *attr)
{
	return __bpf_object__open_xattr(attr, 0);
}