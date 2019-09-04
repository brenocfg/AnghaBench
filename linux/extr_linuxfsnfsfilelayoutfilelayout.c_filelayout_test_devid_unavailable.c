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
struct nfs4_deviceid_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ filelayout_test_devid_invalid (struct nfs4_deviceid_node*) ; 
 scalar_t__ nfs4_test_deviceid_unavailable (struct nfs4_deviceid_node*) ; 

bool
filelayout_test_devid_unavailable(struct nfs4_deviceid_node *node)
{
	return filelayout_test_devid_invalid(node) ||
		nfs4_test_deviceid_unavailable(node);
}