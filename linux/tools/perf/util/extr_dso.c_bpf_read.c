#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  env; } ;
struct dso {TYPE_2__ data; TYPE_1__ bpf_prog; } ;
struct bpf_prog_info_node {TYPE_4__* info_linear; } ;
typedef  int ssize_t ;
struct TYPE_7__ {scalar_t__ jited_prog_len; scalar_t__ jited_prog_insns; } ;
struct TYPE_8__ {TYPE_3__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_DATA_STATUS_ERROR ; 
 int DSO__DATA_CACHE_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct bpf_prog_info_node* perf_env__find_bpf_prog_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t bpf_read(struct dso *dso, u64 offset, char *data)
{
	struct bpf_prog_info_node *node;
	ssize_t size = DSO__DATA_CACHE_SIZE;
	u64 len;
	u8 *buf;

	node = perf_env__find_bpf_prog_info(dso->bpf_prog.env, dso->bpf_prog.id);
	if (!node || !node->info_linear) {
		dso->data.status = DSO_DATA_STATUS_ERROR;
		return -1;
	}

	len = node->info_linear->info.jited_prog_len;
	buf = (u8 *)(uintptr_t)node->info_linear->info.jited_prog_insns;

	if (offset >= len)
		return -1;

	size = (ssize_t)min(len - offset, (u64)size);
	memcpy(data, buf + offset, size);
	return size;
}