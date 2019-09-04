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
struct hci_conn {scalar_t__ sec_level; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 scalar_t__ BT_SECURITY_FIPS ; 
 scalar_t__ BT_SECURITY_HIGH ; 

int hci_conn_check_secure(struct hci_conn *conn, __u8 sec_level)
{
	BT_DBG("hcon %p", conn);

	/* Accept if non-secure or higher security level is required */
	if (sec_level != BT_SECURITY_HIGH && sec_level != BT_SECURITY_FIPS)
		return 1;

	/* Accept if secure or higher security level is already present */
	if (conn->sec_level == BT_SECURITY_HIGH ||
	    conn->sec_level == BT_SECURITY_FIPS)
		return 1;

	/* Reject not secure link */
	return 0;
}