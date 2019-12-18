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
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static inline int emit(char *buf, int buflen, int rbot, int rtop, int len)
{
	if (len > 0)
		len += snprintf(buf + len, max(buflen - len, 0), ",");
	if (rbot == rtop)
		len += snprintf(buf + len, max(buflen - len, 0), "%d", rbot);
	else
		len += snprintf(buf + len, max(buflen - len, 0), "%d-%d",
				rbot, rtop);
	return len;
}