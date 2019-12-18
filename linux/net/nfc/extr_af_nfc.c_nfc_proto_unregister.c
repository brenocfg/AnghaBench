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
 int /*<<< orphan*/ ** proto_tab ; 
 int /*<<< orphan*/  proto_tab_lock ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void nfc_proto_unregister(const struct nfc_protocol *nfc_proto)
{
	write_lock(&proto_tab_lock);
	proto_tab[nfc_proto->id] = NULL;
	write_unlock(&proto_tab_lock);

	proto_unregister(nfc_proto->proto);
}