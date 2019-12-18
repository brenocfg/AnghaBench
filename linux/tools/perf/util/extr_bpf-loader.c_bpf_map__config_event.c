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
struct parse_events_term {scalar_t__ type_val; int /*<<< orphan*/  err_val; } ;
struct evlist {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__OBJCONF_CONF ; 
 int BPF_LOADER_ERRNO__OBJCONF_MAP_VALUE ; 
 scalar_t__ PARSE_EVENTS__TERM_TYPE_STR ; 
 int __bpf_map__config_event (struct bpf_map*,struct parse_events_term*,struct evlist*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int
bpf_map__config_event(struct bpf_map *map,
		      struct parse_events_term *term,
		      struct evlist *evlist)
{
	if (!term->err_val) {
		pr_debug("Config value not set\n");
		return -BPF_LOADER_ERRNO__OBJCONF_CONF;
	}

	if (term->type_val != PARSE_EVENTS__TERM_TYPE_STR) {
		pr_debug("ERROR: wrong value type for 'event'\n");
		return -BPF_LOADER_ERRNO__OBJCONF_MAP_VALUE;
	}

	return __bpf_map__config_event(map, term, evlist);
}