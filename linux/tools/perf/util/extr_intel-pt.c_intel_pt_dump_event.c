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
struct intel_pt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_dump (struct intel_pt*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void intel_pt_dump_event(struct intel_pt *pt, unsigned char *buf,
				size_t len)
{
	printf(".\n");
	intel_pt_dump(pt, buf, len);
}