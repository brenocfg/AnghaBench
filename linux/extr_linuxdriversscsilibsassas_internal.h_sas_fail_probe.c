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
struct domain_device {int /*<<< orphan*/  port; int /*<<< orphan*/  sas_addr; scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_DPRINTK (char*,char const*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sas_unregister_dev (int /*<<< orphan*/ ,struct domain_device*) ; 

__attribute__((used)) static inline void sas_fail_probe(struct domain_device *dev, const char *func, int err)
{
	SAS_DPRINTK("%s: for %s device %16llx returned %d\n",
		    func, dev->parent ? "exp-attached" :
					    "direct-attached",
		    SAS_ADDR(dev->sas_addr), err);
	sas_unregister_dev(dev->port, dev);
}