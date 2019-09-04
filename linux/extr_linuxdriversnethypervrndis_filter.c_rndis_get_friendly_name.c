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
typedef  int /*<<< orphan*/  wname ;
typedef  int /*<<< orphan*/  ucs2_char_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rndis_device {int dummy; } ;
struct netvsc_device {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  ifalias ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_OID_GEN_FRIENDLY_NAME ; 
 int /*<<< orphan*/  dev_set_alias (struct net_device*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ rndis_filter_query_device (struct rndis_device*,struct netvsc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 unsigned long ucs2_as_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rndis_get_friendly_name(struct net_device *net,
				    struct rndis_device *rndis_device,
				    struct netvsc_device *net_device)
{
	ucs2_char_t wname[256];
	unsigned long len;
	u8 ifalias[256];
	u32 size;

	size = sizeof(wname);
	if (rndis_filter_query_device(rndis_device, net_device,
				      RNDIS_OID_GEN_FRIENDLY_NAME,
				      wname, &size) != 0)
		return;	/* ignore if host does not support */

	if (size == 0)
		return;	/* name not set */

	/* Convert Windows Unicode string to UTF-8 */
	len = ucs2_as_utf8(ifalias, wname, sizeof(ifalias));

	/* ignore the default value from host */
	if (strcmp(ifalias, "Network Adapter") != 0)
		dev_set_alias(net, ifalias, len);
}