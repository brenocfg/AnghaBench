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
struct s390_cpumsf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  s390_cpumsf_dump (struct s390_cpumsf*,unsigned char*,size_t) ; 

__attribute__((used)) static void s390_cpumsf_dump_event(struct s390_cpumsf *sf, unsigned char *buf,
				   size_t len)
{
	printf(".\n");
	s390_cpumsf_dump(sf, buf, len);
}