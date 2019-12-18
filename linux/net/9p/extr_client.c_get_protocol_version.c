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
 int EINVAL ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*) ; 
 int p9_proto_2000L ; 
 int p9_proto_2000u ; 
 int p9_proto_legacy ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int get_protocol_version(char *s)
{
	int version = -EINVAL;

	if (!strcmp(s, "9p2000")) {
		version = p9_proto_legacy;
		p9_debug(P9_DEBUG_9P, "Protocol version: Legacy\n");
	} else if (!strcmp(s, "9p2000.u")) {
		version = p9_proto_2000u;
		p9_debug(P9_DEBUG_9P, "Protocol version: 9P2000.u\n");
	} else if (!strcmp(s, "9p2000.L")) {
		version = p9_proto_2000L;
		p9_debug(P9_DEBUG_9P, "Protocol version: 9P2000.L\n");
	} else
		pr_info("Unknown protocol version %s\n", s);

	return version;
}