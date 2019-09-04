#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int disable_unicast_decryption; } ;
struct ipw_priv {TYPE_1__ sys_config; TYPE_2__* ieee; } ;
struct TYPE_4__ {int host_decrypt; scalar_t__ host_encrypt; } ;

/* Variables and functions */
#define  SEC_LEVEL_0 131 
#define  SEC_LEVEL_1 130 
#define  SEC_LEVEL_2 129 
#define  SEC_LEVEL_3 128 

__attribute__((used)) static void ipw_set_hw_decrypt_unicast(struct ipw_priv *priv, int level)
{
	if (priv->ieee->host_encrypt)
		return;

	switch (level) {
	case SEC_LEVEL_3:
		priv->sys_config.disable_unicast_decryption = 0;
		priv->ieee->host_decrypt = 0;
		break;
	case SEC_LEVEL_2:
		priv->sys_config.disable_unicast_decryption = 1;
		priv->ieee->host_decrypt = 1;
		break;
	case SEC_LEVEL_1:
		priv->sys_config.disable_unicast_decryption = 0;
		priv->ieee->host_decrypt = 0;
		break;
	case SEC_LEVEL_0:
		priv->sys_config.disable_unicast_decryption = 1;
		break;
	default:
		break;
	}
}