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
typedef  int u32 ;
struct bpf_prog_array_item {int dummy; } ;
struct bpf_prog_array {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct bpf_prog_array hdr; } ;

/* Variables and functions */
 TYPE_1__ empty_prog_array ; 
 struct bpf_prog_array* kzalloc (int,int /*<<< orphan*/ ) ; 

struct bpf_prog_array *bpf_prog_array_alloc(u32 prog_cnt, gfp_t flags)
{
	if (prog_cnt)
		return kzalloc(sizeof(struct bpf_prog_array) +
			       sizeof(struct bpf_prog_array_item) *
			       (prog_cnt + 1),
			       flags);

	return &empty_prog_array.hdr;
}