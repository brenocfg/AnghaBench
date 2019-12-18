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
struct ip_vs_service {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  ip_vs_unlink_service (struct ip_vs_service*,int) ; 

__attribute__((used)) static int ip_vs_del_service(struct ip_vs_service *svc)
{
	if (svc == NULL)
		return -EEXIST;
	ip_vs_unlink_service(svc, false);

	return 0;
}