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
struct perf_event_attr {char precise_ip; int exclude_guest; scalar_t__ exclude_host; scalar_t__ exclude_hv; scalar_t__ exclude_user; scalar_t__ exclude_kernel; } ;
struct perf_evsel {struct perf_event_attr attr; } ;

/* Variables and functions */
 scalar_t__ scnprintf (char*,size_t,char*,char,...) ; 

__attribute__((used)) static int perf_evsel__add_modifiers(struct perf_evsel *evsel, char *bf, size_t size)
{
	int colon = 0, r = 0;
	struct perf_event_attr *attr = &evsel->attr;
	bool exclude_guest_default = false;

#define MOD_PRINT(context, mod)	do {					\
		if (!attr->exclude_##context) {				\
			if (!colon) colon = ++r;			\
			r += scnprintf(bf + r, size - r, "%c", mod);	\
		} } while(0)

	if (attr->exclude_kernel || attr->exclude_user || attr->exclude_hv) {
		MOD_PRINT(kernel, 'k');
		MOD_PRINT(user, 'u');
		MOD_PRINT(hv, 'h');
		exclude_guest_default = true;
	}

	if (attr->precise_ip) {
		if (!colon)
			colon = ++r;
		r += scnprintf(bf + r, size - r, "%.*s", attr->precise_ip, "ppp");
		exclude_guest_default = true;
	}

	if (attr->exclude_host || attr->exclude_guest == exclude_guest_default) {
		MOD_PRINT(host, 'H');
		MOD_PRINT(guest, 'G');
	}
#undef MOD_PRINT
	if (colon)
		bf[colon - 1] = ':';
	return r;
}