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
struct nfc_protocol {size_t id; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t NFC_SOCKPROTO_MAX ; 
 int proto_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfc_protocol const** proto_tab ; 
 int /*<<< orphan*/  proto_tab_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int nfc_proto_register(const struct nfc_protocol *nfc_proto)
{
	int rc;

	if (nfc_proto->id < 0 || nfc_proto->id >= NFC_SOCKPROTO_MAX)
		return -EINVAL;

	rc = proto_register(nfc_proto->proto, 0);
	if (rc)
		return rc;

	write_lock(&proto_tab_lock);
	if (proto_tab[nfc_proto->id])
		rc = -EBUSY;
	else
		proto_tab[nfc_proto->id] = nfc_proto;
	write_unlock(&proto_tab_lock);

	return rc;
}