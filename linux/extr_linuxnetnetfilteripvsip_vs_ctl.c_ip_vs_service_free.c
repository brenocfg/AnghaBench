#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cpustats; } ;
struct ip_vs_service {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ip_vs_service*) ; 

__attribute__((used)) static void ip_vs_service_free(struct ip_vs_service *svc)
{
	free_percpu(svc->stats.cpustats);
	kfree(svc);
}