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
typedef  int /*<<< orphan*/  u8 ;
struct xenbus_device {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int ENOENT ; 
 int ETH_ALEN ; 
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  simple_strtoul (char*,char**,int) ; 
 char* xenbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xen_net_read_mac(struct xenbus_device *dev, u8 mac[])
{
	char *s, *e, *macstr;
	int i;

	macstr = s = xenbus_read(XBT_NIL, dev->nodename, "mac", NULL);
	if (IS_ERR(macstr))
		return PTR_ERR(macstr);

	for (i = 0; i < ETH_ALEN; i++) {
		mac[i] = simple_strtoul(s, &e, 16);
		if ((s == e) || (*e != ((i == ETH_ALEN-1) ? '\0' : ':'))) {
			kfree(macstr);
			return -ENOENT;
		}
		s = e+1;
	}

	kfree(macstr);
	return 0;
}