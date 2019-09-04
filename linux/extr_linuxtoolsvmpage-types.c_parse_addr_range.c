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
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  add_addr_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  fatal (char*,unsigned long,unsigned long) ; 
 unsigned long parse_number (char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void parse_addr_range(const char *optarg)
{
	unsigned long offset;
	unsigned long size;
	char *p;

	p = strchr(optarg, ',');
	if (!p)
		p = strchr(optarg, '+');

	if (p == optarg) {
		offset = 0;
		size   = parse_number(p + 1);
	} else if (p) {
		offset = parse_number(optarg);
		if (p[1] == '\0')
			size = ULONG_MAX;
		else {
			size = parse_number(p + 1);
			if (*p == ',') {
				if (size < offset)
					fatal("invalid range: %lu,%lu\n",
							offset, size);
				size -= offset;
			}
		}
	} else {
		offset = parse_number(optarg);
		size   = 1;
	}

	add_addr_range(offset, size);
}