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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 char* if_indextoname (scalar_t__,char*) ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ifindex_to_name_ns(__u32 ifindex, __u32 ns_dev, __u32 ns_ino, char *buf)
{
	struct stat st;
	int err;

	err = stat("/proc/self/ns/net", &st);
	if (err) {
		p_err("Can't stat /proc/self: %s", strerror(errno));
		return NULL;
	}

	if (st.st_dev != ns_dev || st.st_ino != ns_ino)
		return NULL;

	return if_indextoname(ifindex, buf);
}