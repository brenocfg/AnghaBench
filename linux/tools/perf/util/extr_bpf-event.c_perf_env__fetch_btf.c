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
typedef  void* u32 ;
struct perf_env {int dummy; } ;
struct btf_node {int /*<<< orphan*/  data; void* data_size; void* id; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 void* btf__get_raw_data (struct btf*,void**) ; 
 struct btf_node* malloc (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,void*) ; 
 int /*<<< orphan*/  perf_env__insert_btf (struct perf_env*,struct btf_node*) ; 

__attribute__((used)) static int perf_env__fetch_btf(struct perf_env *env,
			       u32 btf_id,
			       struct btf *btf)
{
	struct btf_node *node;
	u32 data_size;
	const void *data;

	data = btf__get_raw_data(btf, &data_size);

	node = malloc(data_size + sizeof(struct btf_node));
	if (!node)
		return -1;

	node->id = btf_id;
	node->data_size = data_size;
	memcpy(node->data, data, data_size);

	perf_env__insert_btf(env, node);
	return 0;
}