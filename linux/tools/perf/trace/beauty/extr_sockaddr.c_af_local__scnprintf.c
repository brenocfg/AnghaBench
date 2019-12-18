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
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t af_local__scnprintf(struct sockaddr *sa, char *bf, size_t size)
{
	struct sockaddr_un *sun = (struct sockaddr_un *)sa;
	return scnprintf(bf, size, ", path: %s", sun->sun_path);
}