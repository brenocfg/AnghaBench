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
struct stat64 {int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct perf_ns_link_info {int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,char const*) ; 
 scalar_t__ stat64 (char*,struct stat64*) ; 

__attribute__((used)) static void perf_event__get_ns_link_info(pid_t pid, const char *ns,
					 struct perf_ns_link_info *ns_link_info)
{
	struct stat64 st;
	char proc_ns[128];

	sprintf(proc_ns, "/proc/%u/ns/%s", pid, ns);
	if (stat64(proc_ns, &st) == 0) {
		ns_link_info->dev = st.st_dev;
		ns_link_info->ino = st.st_ino;
	}
}