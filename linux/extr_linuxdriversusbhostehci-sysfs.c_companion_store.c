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
struct ehci_hcd {int /*<<< orphan*/  companion_ports; int /*<<< orphan*/  hcs_params; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOENT ; 
 int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 int PORT_OWNER ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct ehci_hcd* hcd_to_ehci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_owner (struct ehci_hcd*,int,int) ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t companion_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct ehci_hcd		*ehci;
	int			portnum, new_owner;

	ehci = hcd_to_ehci(dev_get_drvdata(dev));
	new_owner = PORT_OWNER;		/* Owned by companion */
	if (sscanf(buf, "%d", &portnum) != 1)
		return -EINVAL;
	if (portnum < 0) {
		portnum = - portnum;
		new_owner = 0;		/* Owned by EHCI */
	}
	if (portnum <= 0 || portnum > HCS_N_PORTS(ehci->hcs_params))
		return -ENOENT;
	portnum--;
	if (new_owner)
		set_bit(portnum, &ehci->companion_ports);
	else
		clear_bit(portnum, &ehci->companion_ports);
	set_owner(ehci, portnum, new_owner);
	return count;
}