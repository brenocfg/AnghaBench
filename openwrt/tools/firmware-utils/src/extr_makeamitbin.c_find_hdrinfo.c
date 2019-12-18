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
struct hdrinfo {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct hdrinfo* hdrinfo ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

struct hdrinfo *find_hdrinfo(const char *name)
{
	int n;
	for (n = 0; hdrinfo[n].name != NULL; n++)
	{
		if (strcmp(name, hdrinfo[n].name) == 0)
			return &hdrinfo[n];
	}
	return NULL;
}