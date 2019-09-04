#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ks_wlan_private {scalar_t__ dev_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  body; void* type; void* size; } ;
struct hostif_mib_set_request_t {TYPE_1__ mib_value; int /*<<< orphan*/  mib_attribute; } ;
typedef  enum mib_data_type { ____Placeholder_mib_data_type } mib_data_type ;
typedef  enum mib_attribute { ____Placeholder_mib_attribute } mib_attribute ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_BOOT ; 
 int /*<<< orphan*/  HIF_MIB_SET_REQ ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_mib_set_request_t* hostif_generic_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_mib_set_request_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostif_mib_set_request(struct ks_wlan_private *priv,
				   enum mib_attribute attr,
				   enum mib_data_type type,
				   void *data, size_t size)
{
	struct hostif_mib_set_request_t *pp;

	if (priv->dev_state < DEVICE_STATE_BOOT)
		return;

	pp = hostif_generic_request(sizeof(*pp), HIF_MIB_SET_REQ);
	if (!pp)
		return;

	pp->mib_attribute = cpu_to_le32(attr);
	pp->mib_value.size = cpu_to_le16(size);
	pp->mib_value.type = cpu_to_le16(type);
	memcpy(&pp->mib_value.body, data, size);

	send_request_to_device(priv, pp, hif_align_size(sizeof(*pp) + size));
}