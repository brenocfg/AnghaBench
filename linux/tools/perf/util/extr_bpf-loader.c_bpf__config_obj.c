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
struct parse_events_term {int /*<<< orphan*/  config; } ;
struct evlist {int dummy; } ;
struct bpf_object {int dummy; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__OBJCONF_OPT ; 
 int EINVAL ; 
 int bpf__obj_config_map (struct bpf_object*,struct parse_events_term*,struct evlist*,int*) ; 
 scalar_t__ strstarts (int /*<<< orphan*/ ,char*) ; 

int bpf__config_obj(struct bpf_object *obj,
		    struct parse_events_term *term,
		    struct evlist *evlist,
		    int *error_pos)
{
	int key_scan_pos = 0;
	int err;

	if (!obj || !term || !term->config)
		return -EINVAL;

	if (strstarts(term->config, "map:")) {
		key_scan_pos = sizeof("map:") - 1;
		err = bpf__obj_config_map(obj, term, evlist, &key_scan_pos);
		goto out;
	}
	err = -BPF_LOADER_ERRNO__OBJCONF_OPT;
out:
	if (error_pos)
		*error_pos = key_scan_pos;
	return err;

}