#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct r_bin_mdmp_obj* misc_info_1; } ;
struct TYPE_4__ {int /*<<< orphan*/  memories; } ;
struct TYPE_6__ {TYPE_2__ misc_info; struct r_bin_mdmp_obj* function_table; struct r_bin_mdmp_obj* handle_data; struct r_bin_mdmp_obj* comments_w; struct r_bin_mdmp_obj* comments_a; struct r_bin_mdmp_obj* system_info; struct r_bin_mdmp_obj* exception; int /*<<< orphan*/  unloaded_modules; int /*<<< orphan*/  token_infos; int /*<<< orphan*/  threads; int /*<<< orphan*/  thread_infos; int /*<<< orphan*/  operations; int /*<<< orphan*/  modules; int /*<<< orphan*/  memory_infos; TYPE_1__ memories64; int /*<<< orphan*/  memories; int /*<<< orphan*/  ex_threads; } ;
struct r_bin_mdmp_obj {int /*<<< orphan*/ * b; struct r_bin_mdmp_obj* hdr; int /*<<< orphan*/  pe64_bins; int /*<<< orphan*/  pe32_bins; TYPE_3__ streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct r_bin_mdmp_obj*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 

void r_bin_mdmp_free(struct r_bin_mdmp_obj *obj) {
	if (!obj) {
		return;
	}

	r_list_free (obj->streams.ex_threads);
	r_list_free (obj->streams.memories);
	r_list_free (obj->streams.memories64.memories);
	r_list_free (obj->streams.memory_infos);
	r_list_free (obj->streams.modules);
	r_list_free (obj->streams.operations);
	r_list_free (obj->streams.thread_infos);
	r_list_free (obj->streams.threads);
	r_list_free (obj->streams.token_infos);
	r_list_free (obj->streams.unloaded_modules);
	free (obj->streams.exception);
	free (obj->streams.system_info);
	free (obj->streams.comments_a);
	free (obj->streams.comments_w);
	free (obj->streams.handle_data);
	free (obj->streams.function_table);
	free (obj->streams.misc_info.misc_info_1);

	r_list_free (obj->pe32_bins);
	r_list_free (obj->pe64_bins);

	r_buf_free (obj->b);
	free (obj->hdr);
	obj->b = NULL;
	free (obj);

	return;
}