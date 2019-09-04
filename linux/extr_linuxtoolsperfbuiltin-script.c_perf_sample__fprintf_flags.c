#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {char* name; int flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* PERF_IP_FLAG_CHARS ; 
 int PERF_IP_FLAG_IN_TX ; 
 int fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 TYPE_1__* sample_flags ; 
 int strlen (char*) ; 

__attribute__((used)) static int perf_sample__fprintf_flags(u32 flags, FILE *fp)
{
	const char *chars = PERF_IP_FLAG_CHARS;
	const int n = strlen(PERF_IP_FLAG_CHARS);
	bool in_tx = flags & PERF_IP_FLAG_IN_TX;
	const char *name = NULL;
	char str[33];
	int i, pos = 0;

	for (i = 0; sample_flags[i].name ; i++) {
		if (sample_flags[i].flags == (flags & ~PERF_IP_FLAG_IN_TX)) {
			name = sample_flags[i].name;
			break;
		}
	}

	for (i = 0; i < n; i++, flags >>= 1) {
		if (flags & 1)
			str[pos++] = chars[i];
	}
	for (; i < 32; i++, flags >>= 1) {
		if (flags & 1)
			str[pos++] = '?';
	}
	str[pos] = 0;

	if (name)
		return fprintf(fp, "  %-7s%4s ", name, in_tx ? "(x)" : "");

	return fprintf(fp, "  %-11s ", str);
}