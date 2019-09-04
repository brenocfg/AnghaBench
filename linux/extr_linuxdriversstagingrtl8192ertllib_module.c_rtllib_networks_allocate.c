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
struct rtllib_network {int dummy; } ;
struct rtllib_device {scalar_t__ networks; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_NETWORK_COUNT ; 
 scalar_t__ kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rtllib_networks_allocate(struct rtllib_device *ieee)
{
	if (ieee->networks)
		return 0;

	ieee->networks = kcalloc(MAX_NETWORK_COUNT,
				 sizeof(struct rtllib_network), GFP_KERNEL);
	if (!ieee->networks)
		return -ENOMEM;

	return 0;
}