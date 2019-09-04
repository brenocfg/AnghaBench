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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_8822B_DEFAULT_PORT_ID ; 
 int H2C_DEFAULT_PORT_ID_LEN ; 
 int /*<<< orphan*/  SET_H2CCMD_DFTPID_MAC_ID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_DFTPID_PORT_ID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8822be_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void rtl8822be_set_default_port_id_cmd(struct ieee80211_hw *hw)
{
	u8 h2c_set_default_port_id[H2C_DEFAULT_PORT_ID_LEN];

	SET_H2CCMD_DFTPID_PORT_ID(h2c_set_default_port_id, 0);
	SET_H2CCMD_DFTPID_MAC_ID(h2c_set_default_port_id, 0);

	rtl8822be_fill_h2c_cmd(hw, H2C_8822B_DEFAULT_PORT_ID,
			       H2C_DEFAULT_PORT_ID_LEN,
			       h2c_set_default_port_id);
}