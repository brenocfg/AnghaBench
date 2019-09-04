#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct msrmap {scalar_t__ num; } ;
struct TYPE_6__ {int start; } ;
typedef  TYPE_1__ jsmntok_t ;

/* Variables and functions */
 int /*<<< orphan*/  cut_comma (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  json_len (TYPE_1__*) ; 
 scalar_t__ json_streq (char*,TYPE_1__*,scalar_t__) ; 
 struct msrmap* msrmap ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prog ; 

__attribute__((used)) static struct msrmap *lookup_msr(char *map, jsmntok_t *val)
{
	jsmntok_t newval = *val;
	static bool warned;
	int i;

	cut_comma(map, &newval);
	for (i = 0; msrmap[i].num; i++)
		if (json_streq(map, &newval, msrmap[i].num))
			return &msrmap[i];
	if (!warned) {
		warned = true;
		pr_err("%s: Unknown MSR in event file %.*s\n", prog,
			json_len(val), map + val->start);
	}
	return NULL;
}