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
typedef  size_t u8 ;
struct wilc_priv {int /*<<< orphan*/ * wep_key; int /*<<< orphan*/ * wep_key_len; } ;
struct key_params {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wilc_wfi_cfg_copy_wep_info(struct wilc_priv *priv,
					      u8 key_index,
					      struct key_params *params)
{
	priv->wep_key_len[key_index] = params->key_len;
	memcpy(priv->wep_key[key_index], params->key, params->key_len);
}