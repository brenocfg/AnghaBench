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
struct nfc_llcp_local {size_t gb_len; int /*<<< orphan*/ * gb; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfc_llcp_build_gb (struct nfc_llcp_local*) ; 
 struct nfc_llcp_local* nfc_llcp_find_local (struct nfc_dev*) ; 

u8 *nfc_llcp_general_bytes(struct nfc_dev *dev, size_t *general_bytes_len)
{
	struct nfc_llcp_local *local;

	local = nfc_llcp_find_local(dev);
	if (local == NULL) {
		*general_bytes_len = 0;
		return NULL;
	}

	nfc_llcp_build_gb(local);

	*general_bytes_len = local->gb_len;

	return local->gb;
}