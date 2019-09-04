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
typedef  int /*<<< orphan*/  v ;
struct ks_wlan_private {int dummy; } ;
typedef  enum mib_attribute { ____Placeholder_mib_attribute } mib_attribute ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  MIB_VALUE_TYPE_INT ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  hostif_mib_set_request (struct ks_wlan_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static inline void hostif_mib_set_request_int(struct ks_wlan_private *priv,
					      enum mib_attribute attr, int val)
{
	__le32 v = cpu_to_le32(val);
	size_t size = sizeof(v);

	hostif_mib_set_request(priv, attr, MIB_VALUE_TYPE_INT, &v, size);
}