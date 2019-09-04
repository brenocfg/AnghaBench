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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rocker_tlv {int dummy; } ;
struct rocker_port {int dummy; } ;
struct rocker_desc_info {int dummy; } ;
struct TYPE_2__ {int phy_address; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int EIO ; 
 int /*<<< orphan*/  PORT_TP ; 
 size_t ROCKER_TLV_CMD_INFO ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_MAX ; 
 size_t ROCKER_TLV_CMD_PORT_SETTINGS_AUTONEG ; 
 size_t ROCKER_TLV_CMD_PORT_SETTINGS_DUPLEX ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_PORT_SETTINGS_MAX ; 
 size_t ROCKER_TLV_CMD_PORT_SETTINGS_SPEED ; 
 int /*<<< orphan*/  TP ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_tlv_get_u32 (struct rocker_tlv const*) ; 
 scalar_t__ rocker_tlv_get_u8 (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_desc (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_desc_info const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_nested (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_tlv const*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int
rocker_cmd_get_port_settings_ethtool_proc(const struct rocker_port *rocker_port,
					  const struct rocker_desc_info *desc_info,
					  void *priv)
{
	struct ethtool_link_ksettings *ecmd = priv;
	const struct rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	const struct rocker_tlv *info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MAX + 1];
	u32 speed;
	u8 duplex;
	u8 autoneg;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);
	if (!attrs[ROCKER_TLV_CMD_INFO])
		return -EIO;

	rocker_tlv_parse_nested(info_attrs, ROCKER_TLV_CMD_PORT_SETTINGS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);
	if (!info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_SPEED] ||
	    !info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_DUPLEX] ||
	    !info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_AUTONEG])
		return -EIO;

	speed = rocker_tlv_get_u32(info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_SPEED]);
	duplex = rocker_tlv_get_u8(info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_DUPLEX]);
	autoneg = rocker_tlv_get_u8(info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_AUTONEG]);

	ethtool_link_ksettings_zero_link_mode(ecmd, supported);
	ethtool_link_ksettings_add_link_mode(ecmd, supported, TP);

	ecmd->base.phy_address = 0xff;
	ecmd->base.port = PORT_TP;
	ecmd->base.speed = speed;
	ecmd->base.duplex = duplex ? DUPLEX_FULL : DUPLEX_HALF;
	ecmd->base.autoneg = autoneg ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	return 0;
}