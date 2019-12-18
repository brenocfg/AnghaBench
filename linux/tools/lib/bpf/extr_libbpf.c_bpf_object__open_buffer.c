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
typedef  int /*<<< orphan*/  tmp_name ;
struct bpf_object {int dummy; } ;

/* Variables and functions */
 struct bpf_object* __bpf_object__open (char const*,void*,size_t,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long,unsigned long) ; 

struct bpf_object *bpf_object__open_buffer(void *obj_buf,
					   size_t obj_buf_sz,
					   const char *name)
{
	char tmp_name[64];

	/* param validation */
	if (!obj_buf || obj_buf_sz <= 0)
		return NULL;

	if (!name) {
		snprintf(tmp_name, sizeof(tmp_name), "%lx-%lx",
			 (unsigned long)obj_buf,
			 (unsigned long)obj_buf_sz);
		name = tmp_name;
	}
	pr_debug("loading object '%s' from buffer\n", name);

	return __bpf_object__open(name, obj_buf, obj_buf_sz, true, true);
}