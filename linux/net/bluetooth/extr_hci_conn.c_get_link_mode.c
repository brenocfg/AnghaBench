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
typedef  int /*<<< orphan*/  u32 ;
struct hci_conn {scalar_t__ role; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CONN_AUTH ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 int /*<<< orphan*/  HCI_CONN_FIPS ; 
 int /*<<< orphan*/  HCI_CONN_SECURE ; 
 int /*<<< orphan*/  HCI_LM_AUTH ; 
 int /*<<< orphan*/  HCI_LM_ENCRYPT ; 
 int /*<<< orphan*/  HCI_LM_FIPS ; 
 int /*<<< orphan*/  HCI_LM_MASTER ; 
 int /*<<< orphan*/  HCI_LM_SECURE ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 get_link_mode(struct hci_conn *conn)
{
	u32 link_mode = 0;

	if (conn->role == HCI_ROLE_MASTER)
		link_mode |= HCI_LM_MASTER;

	if (test_bit(HCI_CONN_ENCRYPT, &conn->flags))
		link_mode |= HCI_LM_ENCRYPT;

	if (test_bit(HCI_CONN_AUTH, &conn->flags))
		link_mode |= HCI_LM_AUTH;

	if (test_bit(HCI_CONN_SECURE, &conn->flags))
		link_mode |= HCI_LM_SECURE;

	if (test_bit(HCI_CONN_FIPS, &conn->flags))
		link_mode |= HCI_LM_FIPS;

	return link_mode;
}