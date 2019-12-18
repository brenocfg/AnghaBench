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
 size_t scnprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static size_t fcntl__scnprintf_getfd(unsigned long val, char *bf, size_t size, bool show_prefix)
{
	return val ? scnprintf(bf, size, "%s", "0") :
		     scnprintf(bf, size, "%s%s", show_prefix ? "FD_" : "", "CLOEXEC");
}