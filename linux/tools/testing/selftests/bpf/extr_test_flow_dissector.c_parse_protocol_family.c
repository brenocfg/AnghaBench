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

/* Variables and functions */
 int PF_INET ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char const*) ; 

__attribute__((used)) static int parse_protocol_family(const char *filepath, const char *optarg)
{
	if (!strcmp(optarg, "4"))
		return PF_INET;
	if (!strcmp(optarg, "6"))
		return PF_INET6;

	usage(filepath);
}