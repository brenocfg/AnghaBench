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
struct evlist {int dummy; } ;
struct auxtrace_record {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 struct auxtrace_record* auxtrace_record__init_intel (struct evlist*,int*) ; 
 int get_cpuid (char*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

struct auxtrace_record *auxtrace_record__init(struct evlist *evlist,
					      int *err)
{
	char buffer[64];
	int ret;

	*err = 0;

	ret = get_cpuid(buffer, sizeof(buffer));
	if (ret) {
		*err = ret;
		return NULL;
	}

	if (!strncmp(buffer, "GenuineIntel,", 13))
		return auxtrace_record__init_intel(evlist, err);

	return NULL;
}