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
struct TYPE_6__ {int /*<<< orphan*/  file_size; int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  env; } ;
struct dso {TYPE_2__ data; TYPE_1__ bpf_prog; } ;
struct bpf_prog_info_node {TYPE_3__* info_linear; } ;
struct TYPE_8__ {int /*<<< orphan*/  jited_prog_len; } ;
struct TYPE_7__ {TYPE_4__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_DATA_STATUS_ERROR ; 
 struct bpf_prog_info_node* perf_env__find_bpf_prog_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_size(struct dso *dso)
{
	struct bpf_prog_info_node *node;

	node = perf_env__find_bpf_prog_info(dso->bpf_prog.env, dso->bpf_prog.id);
	if (!node || !node->info_linear) {
		dso->data.status = DSO_DATA_STATUS_ERROR;
		return -1;
	}

	dso->data.file_size = node->info_linear->info.jited_prog_len;
	return 0;
}