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
typedef  int u8 ;
struct rt305x_esw {int reg_initval_fct2; int reg_initval_fpa2; int port_disable; int reg_led_polarity; int port_map; int /*<<< orphan*/  swdev; TYPE_1__* ports; } ;
struct TYPE_2__ {int disable; int led; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_PDOWN ; 
 int BMCR_SPEED100 ; 
 int MII_BMCR ; 
 scalar_t__ MT762X_SOC_MT7628AN ; 
 scalar_t__ MT762X_SOC_MT7688 ; 
 int RT305X_ESW_NUM_LEDS ; 
 int RT305X_ESW_PFC1_EN_VLAN_S ; 
 int RT305X_ESW_PMAP_LLLLLL ; 
 int RT305X_ESW_POC0_EN_BP_S ; 
 int RT305X_ESW_POC0_EN_FC_S ; 
 int RT305X_ESW_POC2_ENAGING_S ; 
 int RT305X_ESW_POC2_UNTAG_EN_S ; 
 int RT305X_ESW_PORTS_ALL ; 
 int RT305X_ESW_PORTS_CPU ; 
 int RT305X_ESW_PORTS_NOCPU ; 
 int RT305X_ESW_PORT_ST_CHG ; 
 int /*<<< orphan*/  RT305X_ESW_REG_FCT0 ; 
 int /*<<< orphan*/  RT305X_ESW_REG_FCT2 ; 
 int /*<<< orphan*/  RT305X_ESW_REG_FPA ; 
 int /*<<< orphan*/  RT305X_ESW_REG_FPA2 ; 
 int /*<<< orphan*/  RT305X_ESW_REG_IMR ; 
 int /*<<< orphan*/  RT305X_ESW_REG_P0LED ; 
 int /*<<< orphan*/  RT305X_ESW_REG_P1LED ; 
 int /*<<< orphan*/  RT305X_ESW_REG_P2LED ; 
 int /*<<< orphan*/  RT305X_ESW_REG_P3LED ; 
 int /*<<< orphan*/  RT305X_ESW_REG_P4LED ; 
 int /*<<< orphan*/  RT305X_ESW_REG_PFC1 ; 
 int /*<<< orphan*/  RT305X_ESW_REG_POC0 ; 
 int /*<<< orphan*/  RT305X_ESW_REG_POC2 ; 
 int /*<<< orphan*/  RT305X_ESW_REG_SGC ; 
 int /*<<< orphan*/  RT305X_ESW_REG_SGC2 ; 
 int /*<<< orphan*/  RT305X_ESW_REG_SOCPC ; 
 int RT305X_ESW_SGC2_LAN_PMAP_M ; 
 int RT305X_ESW_SGC2_LAN_PMAP_S ; 
 int RT305X_ESW_SOCPC_CRC_PADDING ; 
 int RT305X_ESW_SOCPC_DISBC2CPU_S ; 
 int RT305X_ESW_SOCPC_DISMC2CPU_S ; 
 int RT305X_ESW_SOCPC_DISUN2CPU_S ; 
 scalar_t__ RT305X_SOC_RT3352 ; 
 scalar_t__ RT305X_SOC_RT5350 ; 
 int /*<<< orphan*/  RT5350_EWS_REG_LED_POLARITY ; 
 int /*<<< orphan*/  RT5350_RESET_EPHY ; 
 int /*<<< orphan*/  esw_apply_config (int /*<<< orphan*/ *) ; 
 int esw_get_port_disable (struct rt305x_esw*) ; 
 int /*<<< orphan*/  esw_rmw (struct rt305x_esw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  esw_w32 (struct rt305x_esw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ ralink_soc ; 
 int /*<<< orphan*/  rt305x_mii_write (struct rt305x_esw*,int,int,int) ; 

__attribute__((used)) static void esw_hw_init(struct rt305x_esw *esw)
{
	int i;
	u8 port_disable = 0;
	u8 port_map = RT305X_ESW_PMAP_LLLLLL;

	/* vodoo from original driver */
	esw_w32(esw, 0xC8A07850, RT305X_ESW_REG_FCT0);
	esw_w32(esw, 0x00000000, RT305X_ESW_REG_SGC2);
	/* Port priority 1 for all ports, vlan enabled. */
	esw_w32(esw, 0x00005555 |
		     (RT305X_ESW_PORTS_ALL << RT305X_ESW_PFC1_EN_VLAN_S),
		RT305X_ESW_REG_PFC1);

	/* Enable all ports, Back Pressure and Flow Control */
	esw_w32(esw, ((RT305X_ESW_PORTS_ALL << RT305X_ESW_POC0_EN_BP_S) |
		      (RT305X_ESW_PORTS_ALL << RT305X_ESW_POC0_EN_FC_S)),
		RT305X_ESW_REG_POC0);

	/* Enable Aging, and VLAN TAG removal */
	esw_w32(esw, ((RT305X_ESW_PORTS_ALL << RT305X_ESW_POC2_ENAGING_S) |
		      (RT305X_ESW_PORTS_NOCPU << RT305X_ESW_POC2_UNTAG_EN_S)),
		RT305X_ESW_REG_POC2);

	if (esw->reg_initval_fct2)
		esw_w32(esw, esw->reg_initval_fct2, RT305X_ESW_REG_FCT2);
	else
		esw_w32(esw, 0x0002500c, RT305X_ESW_REG_FCT2);

	/* 300s aging timer, max packet len 1536, broadcast storm prevention
	 * disabled, disable collision abort, mac xor48 hash, 10 packet back
	 * pressure jam, GMII disable was_transmit, back pressure disabled,
	 * 30ms led flash, unmatched IGMP as broadcast, rmc tb fault to all
	 * ports.
	 */
	esw_w32(esw, 0x0008a301, RT305X_ESW_REG_SGC);

	/* Setup SoC Port control register */
	esw_w32(esw,
		(RT305X_ESW_SOCPC_CRC_PADDING |
		(RT305X_ESW_PORTS_CPU << RT305X_ESW_SOCPC_DISUN2CPU_S) |
		(RT305X_ESW_PORTS_CPU << RT305X_ESW_SOCPC_DISMC2CPU_S) |
		(RT305X_ESW_PORTS_CPU << RT305X_ESW_SOCPC_DISBC2CPU_S)),
		RT305X_ESW_REG_SOCPC);

	/* ext phy base addr 31, enable port 5 polling, rx/tx clock skew 1,
	 * turbo mii off, rgmi 3.3v off
	 * port5: disabled
	 * port6: enabled, gige, full-duplex, rx/tx-flow-control
	 */
	if (esw->reg_initval_fpa2)
		esw_w32(esw, esw->reg_initval_fpa2, RT305X_ESW_REG_FPA2);
	else
		esw_w32(esw, 0x3f502b28, RT305X_ESW_REG_FPA2);
	esw_w32(esw, 0x00000000, RT305X_ESW_REG_FPA);

	/* Force Link/Activity on ports */
	esw_w32(esw, 0x00000005, RT305X_ESW_REG_P0LED);
	esw_w32(esw, 0x00000005, RT305X_ESW_REG_P1LED);
	esw_w32(esw, 0x00000005, RT305X_ESW_REG_P2LED);
	esw_w32(esw, 0x00000005, RT305X_ESW_REG_P3LED);
	esw_w32(esw, 0x00000005, RT305X_ESW_REG_P4LED);

	/* Copy disabled port configuration from device tree setup */
	port_disable = esw->port_disable;

	/* Disable nonexistent ports by reading the switch config
	 * after having enabled all possible ports above
	 */
	port_disable |= esw_get_port_disable(esw);

	for (i = 0; i < 6; i++)
		esw->ports[i].disable = (port_disable & (1 << i)) != 0;

	if (ralink_soc == RT305X_SOC_RT3352) {
		/* reset EPHY */
		fe_reset(RT5350_RESET_EPHY);

		rt305x_mii_write(esw, 0, 31, 0x8000);
		for (i = 0; i < 5; i++) {
			if (esw->ports[i].disable) {
				rt305x_mii_write(esw, i, MII_BMCR, BMCR_PDOWN);
			} else {
				rt305x_mii_write(esw, i, MII_BMCR,
						 BMCR_FULLDPLX |
						 BMCR_ANENABLE |
						 BMCR_SPEED100);
			}
			/* TX10 waveform coefficient LSB=0 disable PHY */
			rt305x_mii_write(esw, i, 26, 0x1601);
			/* TX100/TX10 AD/DA current bias */
			rt305x_mii_write(esw, i, 29, 0x7016);
			/* TX100 slew rate control */
			rt305x_mii_write(esw, i, 30, 0x0038);
		}

		/* select global register */
		rt305x_mii_write(esw, 0, 31, 0x0);
		/* enlarge agcsel threshold 3 and threshold 2 */
		rt305x_mii_write(esw, 0, 1, 0x4a40);
		/* enlarge agcsel threshold 5 and threshold 4 */
		rt305x_mii_write(esw, 0, 2, 0x6254);
		/* enlarge agcsel threshold  */
		rt305x_mii_write(esw, 0, 3, 0xa17f);
		rt305x_mii_write(esw, 0, 12, 0x7eaa);
		/* longer TP_IDL tail length */
		rt305x_mii_write(esw, 0, 14, 0x65);
		/* increased squelch pulse count threshold. */
		rt305x_mii_write(esw, 0, 16, 0x0684);
		/* set TX10 signal amplitude threshold to minimum */
		rt305x_mii_write(esw, 0, 17, 0x0fe0);
		/* set squelch amplitude to higher threshold */
		rt305x_mii_write(esw, 0, 18, 0x40ba);
		/* tune TP_IDL tail and head waveform, enable power
		 * down slew rate control
		 */
		rt305x_mii_write(esw, 0, 22, 0x253f);
		/* set PLL/Receive bias current are calibrated */
		rt305x_mii_write(esw, 0, 27, 0x2fda);
		/* change PLL/Receive bias current to internal(RT3350) */
		rt305x_mii_write(esw, 0, 28, 0xc410);
		/* change PLL bias current to internal(RT3052_MP3) */
		rt305x_mii_write(esw, 0, 29, 0x598b);
		/* select local register */
		rt305x_mii_write(esw, 0, 31, 0x8000);
	} else if (ralink_soc == RT305X_SOC_RT5350) {
		/* reset EPHY */
		fe_reset(RT5350_RESET_EPHY);

		/* set the led polarity */
		esw_w32(esw, esw->reg_led_polarity & 0x1F,
			RT5350_EWS_REG_LED_POLARITY);

		/* local registers */
		rt305x_mii_write(esw, 0, 31, 0x8000);
		for (i = 0; i < 5; i++) {
			if (esw->ports[i].disable) {
				rt305x_mii_write(esw, i, MII_BMCR, BMCR_PDOWN);
			} else {
				rt305x_mii_write(esw, i, MII_BMCR,
						 BMCR_FULLDPLX |
						 BMCR_ANENABLE |
						 BMCR_SPEED100);
			}
			/* TX10 waveform coefficient LSB=0 disable PHY */
			rt305x_mii_write(esw, i, 26, 0x1601);
			/* TX100/TX10 AD/DA current bias */
			rt305x_mii_write(esw, i, 29, 0x7015);
			/* TX100 slew rate control */
			rt305x_mii_write(esw, i, 30, 0x0038);
		}

		/* global registers */
		rt305x_mii_write(esw, 0, 31, 0x0);
		/* enlarge agcsel threshold 3 and threshold 2 */
		rt305x_mii_write(esw, 0, 1, 0x4a40);
		/* enlarge agcsel threshold 5 and threshold 4 */
		rt305x_mii_write(esw, 0, 2, 0x6254);
		/* enlarge agcsel threshold 6 */
		rt305x_mii_write(esw, 0, 3, 0xa17f);
		rt305x_mii_write(esw, 0, 12, 0x7eaa);
		/* longer TP_IDL tail length */
		rt305x_mii_write(esw, 0, 14, 0x65);
		/* increased squelch pulse count threshold. */
		rt305x_mii_write(esw, 0, 16, 0x0684);
		/* set TX10 signal amplitude threshold to minimum */
		rt305x_mii_write(esw, 0, 17, 0x0fe0);
		/* set squelch amplitude to higher threshold */
		rt305x_mii_write(esw, 0, 18, 0x40ba);
		/* tune TP_IDL tail and head waveform, enable power
		 * down slew rate control
		 */
		rt305x_mii_write(esw, 0, 22, 0x253f);
		/* set PLL/Receive bias current are calibrated */
		rt305x_mii_write(esw, 0, 27, 0x2fda);
		/* change PLL/Receive bias current to internal(RT3350) */
		rt305x_mii_write(esw, 0, 28, 0xc410);
		/* change PLL bias current to internal(RT3052_MP3) */
		rt305x_mii_write(esw, 0, 29, 0x598b);
		/* select local register */
		rt305x_mii_write(esw, 0, 31, 0x8000);
	} else if (ralink_soc == MT762X_SOC_MT7628AN || ralink_soc == MT762X_SOC_MT7688) {
		int i;

		/* reset EPHY */
		fe_reset(RT5350_RESET_EPHY);

		rt305x_mii_write(esw, 0, 31, 0x2000); /* change G2 page */
		rt305x_mii_write(esw, 0, 26, 0x0020);

		for (i = 0; i < 5; i++) {
			rt305x_mii_write(esw, i, 31, 0x8000);
			rt305x_mii_write(esw, i,  0, 0x3100);
			rt305x_mii_write(esw, i, 30, 0xa000);
			rt305x_mii_write(esw, i, 31, 0xa000);
			rt305x_mii_write(esw, i, 16, 0x0606);
			rt305x_mii_write(esw, i, 23, 0x0f0e);
			rt305x_mii_write(esw, i, 24, 0x1610);
			rt305x_mii_write(esw, i, 30, 0x1f15);
			rt305x_mii_write(esw, i, 28, 0x6111);
			rt305x_mii_write(esw, i, 31, 0x2000);
			rt305x_mii_write(esw, i, 26, 0x0000);
		}

		/* 100Base AOI setting */
		rt305x_mii_write(esw, 0, 31, 0x5000);
		rt305x_mii_write(esw, 0, 19, 0x004a);
		rt305x_mii_write(esw, 0, 20, 0x015a);
		rt305x_mii_write(esw, 0, 21, 0x00ee);
		rt305x_mii_write(esw, 0, 22, 0x0033);
		rt305x_mii_write(esw, 0, 23, 0x020a);
		rt305x_mii_write(esw, 0, 24, 0x0000);
		rt305x_mii_write(esw, 0, 25, 0x024a);
		rt305x_mii_write(esw, 0, 26, 0x035a);
		rt305x_mii_write(esw, 0, 27, 0x02ee);
		rt305x_mii_write(esw, 0, 28, 0x0233);
		rt305x_mii_write(esw, 0, 29, 0x000a);
		rt305x_mii_write(esw, 0, 30, 0x0000);
	} else {
		rt305x_mii_write(esw, 0, 31, 0x8000);
		for (i = 0; i < 5; i++) {
			if (esw->ports[i].disable) {
				rt305x_mii_write(esw, i, MII_BMCR, BMCR_PDOWN);
			} else {
				rt305x_mii_write(esw, i, MII_BMCR,
						 BMCR_FULLDPLX |
						 BMCR_ANENABLE |
						 BMCR_SPEED100);
			}
			/* TX10 waveform coefficient */
			rt305x_mii_write(esw, i, 26, 0x1601);
			/* TX100/TX10 AD/DA current bias */
			rt305x_mii_write(esw, i, 29, 0x7058);
			/* TX100 slew rate control */
			rt305x_mii_write(esw, i, 30, 0x0018);
		}

		/* PHY IOT */
		/* select global register */
		rt305x_mii_write(esw, 0, 31, 0x0);
		/* tune TP_IDL tail and head waveform */
		rt305x_mii_write(esw, 0, 22, 0x052f);
		/* set TX10 signal amplitude threshold to minimum */
		rt305x_mii_write(esw, 0, 17, 0x0fe0);
		/* set squelch amplitude to higher threshold */
		rt305x_mii_write(esw, 0, 18, 0x40ba);
		/* longer TP_IDL tail length */
		rt305x_mii_write(esw, 0, 14, 0x65);
		/* select local register */
		rt305x_mii_write(esw, 0, 31, 0x8000);
	}

	if (esw->port_map)
		port_map = esw->port_map;
	else
		port_map = RT305X_ESW_PMAP_LLLLLL;

	/* Unused HW feature, but still nice to be consistent here...
	 * This is also exported to userspace ('lan' attribute) so it's
	 * conveniently usable to decide which ports go into the wan vlan by
	 * default.
	 */
	esw_rmw(esw, RT305X_ESW_REG_SGC2,
		RT305X_ESW_SGC2_LAN_PMAP_M << RT305X_ESW_SGC2_LAN_PMAP_S,
		port_map << RT305X_ESW_SGC2_LAN_PMAP_S);

	/* make the switch leds blink */
	for (i = 0; i < RT305X_ESW_NUM_LEDS; i++)
		esw->ports[i].led = 0x05;

	/* Apply the empty config. */
	esw_apply_config(&esw->swdev);

	/* Only unmask the port change interrupt */
	esw_w32(esw, ~RT305X_ESW_PORT_ST_CHG, RT305X_ESW_REG_IMR);
}