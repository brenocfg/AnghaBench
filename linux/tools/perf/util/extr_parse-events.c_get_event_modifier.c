#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int exclude_user; int exclude_kernel; int exclude_hv; int exclude_host; int exclude_guest; int exclude_idle; int precise_ip; int pinned; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {int exclude_GH; TYPE_2__ core; } ;
struct event_modifier {int eu; int ek; int eh; int eH; int eG; int eI; int precise; int precise_max; int exclude_GH; int sample_read; int pinned; int weak; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct event_modifier*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_event_modifier(struct event_modifier *mod, char *str,
			       struct evsel *evsel)
{
	int eu = evsel ? evsel->core.attr.exclude_user : 0;
	int ek = evsel ? evsel->core.attr.exclude_kernel : 0;
	int eh = evsel ? evsel->core.attr.exclude_hv : 0;
	int eH = evsel ? evsel->core.attr.exclude_host : 0;
	int eG = evsel ? evsel->core.attr.exclude_guest : 0;
	int eI = evsel ? evsel->core.attr.exclude_idle : 0;
	int precise = evsel ? evsel->core.attr.precise_ip : 0;
	int precise_max = 0;
	int sample_read = 0;
	int pinned = evsel ? evsel->core.attr.pinned : 0;

	int exclude = eu | ek | eh;
	int exclude_GH = evsel ? evsel->exclude_GH : 0;
	int weak = 0;

	memset(mod, 0, sizeof(*mod));

	while (*str) {
		if (*str == 'u') {
			if (!exclude)
				exclude = eu = ek = eh = 1;
			eu = 0;
		} else if (*str == 'k') {
			if (!exclude)
				exclude = eu = ek = eh = 1;
			ek = 0;
		} else if (*str == 'h') {
			if (!exclude)
				exclude = eu = ek = eh = 1;
			eh = 0;
		} else if (*str == 'G') {
			if (!exclude_GH)
				exclude_GH = eG = eH = 1;
			eG = 0;
		} else if (*str == 'H') {
			if (!exclude_GH)
				exclude_GH = eG = eH = 1;
			eH = 0;
		} else if (*str == 'I') {
			eI = 1;
		} else if (*str == 'p') {
			precise++;
			/* use of precise requires exclude_guest */
			if (!exclude_GH)
				eG = 1;
		} else if (*str == 'P') {
			precise_max = 1;
		} else if (*str == 'S') {
			sample_read = 1;
		} else if (*str == 'D') {
			pinned = 1;
		} else if (*str == 'W') {
			weak = 1;
		} else
			break;

		++str;
	}

	/*
	 * precise ip:
	 *
	 *  0 - SAMPLE_IP can have arbitrary skid
	 *  1 - SAMPLE_IP must have constant skid
	 *  2 - SAMPLE_IP requested to have 0 skid
	 *  3 - SAMPLE_IP must have 0 skid
	 *
	 *  See also PERF_RECORD_MISC_EXACT_IP
	 */
	if (precise > 3)
		return -EINVAL;

	mod->eu = eu;
	mod->ek = ek;
	mod->eh = eh;
	mod->eH = eH;
	mod->eG = eG;
	mod->eI = eI;
	mod->precise = precise;
	mod->precise_max = precise_max;
	mod->exclude_GH = exclude_GH;
	mod->sample_read = sample_read;
	mod->pinned = pinned;
	mod->weak = weak;

	return 0;
}