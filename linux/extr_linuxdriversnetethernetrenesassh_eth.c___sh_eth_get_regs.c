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
typedef  unsigned int u32 ;
struct sh_eth_private {scalar_t__* reg_offset; scalar_t__ tsu_addr; struct sh_eth_cpu_data* cd; } ;
struct sh_eth_cpu_data {scalar_t__ tsu; scalar_t__ select_mii; scalar_t__ hw_checksum; scalar_t__ rtrate; scalar_t__ bculr; scalar_t__ tpauser; scalar_t__ mpr; scalar_t__ apr; int /*<<< orphan*/  no_psr; int /*<<< orphan*/  no_trimd; scalar_t__ rpadir; scalar_t__ rmiimode; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t APR ; 
 size_t ARSTR ; 
 size_t BCULR ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 size_t CDCR ; 
 size_t CEECR ; 
 size_t CEFCR ; 
 size_t CERCR ; 
 size_t CNDCR ; 
 size_t CSMR ; 
 size_t DIV_ROUND_UP (scalar_t__,int) ; 
 size_t ECMR ; 
 size_t ECSIPR ; 
 size_t ECSR ; 
 size_t EDMR ; 
 size_t EDRRR ; 
 size_t EDSR ; 
 size_t EDTRR ; 
 size_t EESIPR ; 
 size_t EESR ; 
 size_t FCFTR ; 
 size_t FDR ; 
 size_t FRECR ; 
 size_t GECMR ; 
 size_t IPGR ; 
 size_t LCCR ; 
 size_t MAFCR ; 
 size_t MAHR ; 
 size_t MALR ; 
 size_t MPR ; 
 size_t PIR ; 
 size_t PSR ; 
 size_t RDFAR ; 
 size_t RDFFR ; 
 size_t RDFXR ; 
 size_t RDLAR ; 
 size_t RDMLR ; 
 size_t RFCF ; 
 size_t RFCR ; 
 size_t RFLR ; 
 size_t RFOCR ; 
 size_t RMCR ; 
 size_t RMFCR ; 
 size_t RMIIMODE ; 
 size_t RMII_MII ; 
 size_t RPADIR ; 
 size_t RTRATE ; 
 scalar_t__ SH_ETH_MAX_REGISTER_OFFSET ; 
 scalar_t__ SH_ETH_OFFSET_INVALID ; 
 scalar_t__ SH_ETH_REG_DUMP_MAX_REGS ; 
 int SH_ETH_TSU_CAM_ENTRIES ; 
 size_t TDFAR ; 
 size_t TDFFR ; 
 size_t TDFXR ; 
 size_t TDLAR ; 
 size_t TFTR ; 
 size_t TFUCR ; 
 size_t TLFRCR ; 
 size_t TPAUSECR ; 
 size_t TPAUSER ; 
 size_t TRIMD ; 
 size_t TROCR ; 
 size_t TRSCER ; 
 size_t TSFRCR ; 
 size_t TSU_ADQT0 ; 
 size_t TSU_ADQT1 ; 
 int TSU_ADRH0 ; 
 size_t TSU_ADSBSY ; 
 size_t TSU_BSYSL0 ; 
 size_t TSU_BSYSL1 ; 
 size_t TSU_CTRST ; 
 size_t TSU_FCM ; 
 size_t TSU_FWEN0 ; 
 size_t TSU_FWEN1 ; 
 size_t TSU_FWINMK ; 
 size_t TSU_FWSL0 ; 
 size_t TSU_FWSL1 ; 
 size_t TSU_FWSLC ; 
 size_t TSU_FWSR ; 
 size_t TSU_POST1 ; 
 size_t TSU_POST2 ; 
 size_t TSU_POST3 ; 
 size_t TSU_POST4 ; 
 size_t TSU_PRISL0 ; 
 size_t TSU_PRISL1 ; 
 size_t TSU_QTAGM0 ; 
 size_t TSU_QTAGM1 ; 
 size_t TSU_TEN ; 
 size_t TSU_VTAG0 ; 
 size_t TSU_VTAG1 ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 void* sh_eth_read (struct net_device*,size_t) ; 
 void* sh_eth_tsu_read (struct sh_eth_private*,size_t) ; 

__attribute__((used)) static size_t __sh_eth_get_regs(struct net_device *ndev, u32 *buf)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct sh_eth_cpu_data *cd = mdp->cd;
	u32 *valid_map;
	size_t len;

	BUILD_BUG_ON(SH_ETH_MAX_REGISTER_OFFSET > SH_ETH_REG_DUMP_MAX_REGS);

	/* Dump starts with a bitmap that tells ethtool which
	 * registers are defined for this chip.
	 */
	len = DIV_ROUND_UP(SH_ETH_REG_DUMP_MAX_REGS, 32);
	if (buf) {
		valid_map = buf;
		buf += len;
	} else {
		valid_map = NULL;
	}

	/* Add a register to the dump, if it has a defined offset.
	 * This automatically skips most undefined registers, but for
	 * some it is also necessary to check a capability flag in
	 * struct sh_eth_cpu_data.
	 */
#define mark_reg_valid(reg) valid_map[reg / 32] |= 1U << (reg % 32)
#define add_reg_from(reg, read_expr) do {				\
		if (mdp->reg_offset[reg] != SH_ETH_OFFSET_INVALID) {	\
			if (buf) {					\
				mark_reg_valid(reg);			\
				*buf++ = read_expr;			\
			}						\
			++len;						\
		}							\
	} while (0)
#define add_reg(reg) add_reg_from(reg, sh_eth_read(ndev, reg))
#define add_tsu_reg(reg) add_reg_from(reg, sh_eth_tsu_read(mdp, reg))

	add_reg(EDSR);
	add_reg(EDMR);
	add_reg(EDTRR);
	add_reg(EDRRR);
	add_reg(EESR);
	add_reg(EESIPR);
	add_reg(TDLAR);
	add_reg(TDFAR);
	add_reg(TDFXR);
	add_reg(TDFFR);
	add_reg(RDLAR);
	add_reg(RDFAR);
	add_reg(RDFXR);
	add_reg(RDFFR);
	add_reg(TRSCER);
	add_reg(RMFCR);
	add_reg(TFTR);
	add_reg(FDR);
	add_reg(RMCR);
	add_reg(TFUCR);
	add_reg(RFOCR);
	if (cd->rmiimode)
		add_reg(RMIIMODE);
	add_reg(FCFTR);
	if (cd->rpadir)
		add_reg(RPADIR);
	if (!cd->no_trimd)
		add_reg(TRIMD);
	add_reg(ECMR);
	add_reg(ECSR);
	add_reg(ECSIPR);
	add_reg(PIR);
	if (!cd->no_psr)
		add_reg(PSR);
	add_reg(RDMLR);
	add_reg(RFLR);
	add_reg(IPGR);
	if (cd->apr)
		add_reg(APR);
	if (cd->mpr)
		add_reg(MPR);
	add_reg(RFCR);
	add_reg(RFCF);
	if (cd->tpauser)
		add_reg(TPAUSER);
	add_reg(TPAUSECR);
	add_reg(GECMR);
	if (cd->bculr)
		add_reg(BCULR);
	add_reg(MAHR);
	add_reg(MALR);
	add_reg(TROCR);
	add_reg(CDCR);
	add_reg(LCCR);
	add_reg(CNDCR);
	add_reg(CEFCR);
	add_reg(FRECR);
	add_reg(TSFRCR);
	add_reg(TLFRCR);
	add_reg(CERCR);
	add_reg(CEECR);
	add_reg(MAFCR);
	if (cd->rtrate)
		add_reg(RTRATE);
	if (cd->hw_checksum)
		add_reg(CSMR);
	if (cd->select_mii)
		add_reg(RMII_MII);
	if (cd->tsu) {
		add_tsu_reg(ARSTR);
		add_tsu_reg(TSU_CTRST);
		add_tsu_reg(TSU_FWEN0);
		add_tsu_reg(TSU_FWEN1);
		add_tsu_reg(TSU_FCM);
		add_tsu_reg(TSU_BSYSL0);
		add_tsu_reg(TSU_BSYSL1);
		add_tsu_reg(TSU_PRISL0);
		add_tsu_reg(TSU_PRISL1);
		add_tsu_reg(TSU_FWSL0);
		add_tsu_reg(TSU_FWSL1);
		add_tsu_reg(TSU_FWSLC);
		add_tsu_reg(TSU_QTAGM0);
		add_tsu_reg(TSU_QTAGM1);
		add_tsu_reg(TSU_FWSR);
		add_tsu_reg(TSU_FWINMK);
		add_tsu_reg(TSU_ADQT0);
		add_tsu_reg(TSU_ADQT1);
		add_tsu_reg(TSU_VTAG0);
		add_tsu_reg(TSU_VTAG1);
		add_tsu_reg(TSU_ADSBSY);
		add_tsu_reg(TSU_TEN);
		add_tsu_reg(TSU_POST1);
		add_tsu_reg(TSU_POST2);
		add_tsu_reg(TSU_POST3);
		add_tsu_reg(TSU_POST4);
		/* This is the start of a table, not just a single register. */
		if (buf) {
			unsigned int i;

			mark_reg_valid(TSU_ADRH0);
			for (i = 0; i < SH_ETH_TSU_CAM_ENTRIES * 2; i++)
				*buf++ = ioread32(mdp->tsu_addr +
						  mdp->reg_offset[TSU_ADRH0] +
						  i * 4);
		}
		len += SH_ETH_TSU_CAM_ENTRIES * 2;
	}

#undef mark_reg_valid
#undef add_reg_from
#undef add_reg
#undef add_tsu_reg

	return len * 4;
}