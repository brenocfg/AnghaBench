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
struct perf_sample {int /*<<< orphan*/  callchain; } ;
struct map {TYPE_2__* dso; } ;
struct evsel {int dummy; } ;
struct callchain_cursor_node {struct map* map; TYPE_1__* sym; int /*<<< orphan*/  ip; } ;
struct addr_location {int /*<<< orphan*/  thread; } ;
struct TYPE_6__ {scalar_t__ show_kernel_path; int /*<<< orphan*/  use_callchain; } ;
struct TYPE_5__ {char* long_name; char* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  binding; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  HV ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 int /*<<< orphan*/  av_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callchain_cursor ; 
 int /*<<< orphan*/  callchain_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callchain_cursor_commit (int /*<<< orphan*/ *) ; 
 struct callchain_cursor_node* callchain_cursor_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_stores (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_undef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newAV () ; 
 int /*<<< orphan*/ * newHV () ; 
 int /*<<< orphan*/ * newRV_noinc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newSVpv (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newSVpvn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newSVuv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  scripting_max_stack ; 
 TYPE_3__ symbol_conf ; 
 scalar_t__ thread__resolve_callchain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct evsel*,struct perf_sample*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SV *perl_process_callchain(struct perf_sample *sample,
				  struct evsel *evsel,
				  struct addr_location *al)
{
	AV *list;

	list = newAV();
	if (!list)
		goto exit;

	if (!symbol_conf.use_callchain || !sample->callchain)
		goto exit;

	if (thread__resolve_callchain(al->thread, &callchain_cursor, evsel,
				      sample, NULL, NULL, scripting_max_stack) != 0) {
		pr_err("Failed to resolve callchain. Skipping\n");
		goto exit;
	}
	callchain_cursor_commit(&callchain_cursor);


	while (1) {
		HV *elem;
		struct callchain_cursor_node *node;
		node = callchain_cursor_current(&callchain_cursor);
		if (!node)
			break;

		elem = newHV();
		if (!elem)
			goto exit;

		if (!hv_stores(elem, "ip", newSVuv(node->ip))) {
			hv_undef(elem);
			goto exit;
		}

		if (node->sym) {
			HV *sym = newHV();
			if (!sym) {
				hv_undef(elem);
				goto exit;
			}
			if (!hv_stores(sym, "start",   newSVuv(node->sym->start)) ||
			    !hv_stores(sym, "end",     newSVuv(node->sym->end)) ||
			    !hv_stores(sym, "binding", newSVuv(node->sym->binding)) ||
			    !hv_stores(sym, "name",    newSVpvn(node->sym->name,
								node->sym->namelen)) ||
			    !hv_stores(elem, "sym",    newRV_noinc((SV*)sym))) {
				hv_undef(sym);
				hv_undef(elem);
				goto exit;
			}
		}

		if (node->map) {
			struct map *map = node->map;
			const char *dsoname = "[unknown]";
			if (map && map->dso) {
				if (symbol_conf.show_kernel_path && map->dso->long_name)
					dsoname = map->dso->long_name;
				else
					dsoname = map->dso->name;
			}
			if (!hv_stores(elem, "dso", newSVpv(dsoname,0))) {
				hv_undef(elem);
				goto exit;
			}
		}

		callchain_cursor_advance(&callchain_cursor);
		av_push(list, newRV_noinc((SV*)elem));
	}

exit:
	return newRV_noinc((SV*)list);
}