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
struct nuc900_spi {TYPE_1__* pdata; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  txnum; int /*<<< orphan*/  txbitlen; int /*<<< orphan*/  sleep; int /*<<< orphan*/  lsb; int /*<<< orphan*/  rxneg; int /*<<< orphan*/  txneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuc900_enable_int (struct nuc900_spi*) ; 
 int /*<<< orphan*/  nuc900_rx_edge (struct nuc900_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuc900_send_first (struct nuc900_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuc900_set_divider (struct nuc900_spi*) ; 
 int /*<<< orphan*/  nuc900_set_sleep (struct nuc900_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuc900_spi_setup_txbitlen (struct nuc900_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuc900_spi_setup_txnum (struct nuc900_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuc900_tx_edge (struct nuc900_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nuc900_init_spi(struct nuc900_spi *hw)
{
	clk_enable(hw->clk);
	spin_lock_init(&hw->lock);

	nuc900_tx_edge(hw, hw->pdata->txneg);
	nuc900_rx_edge(hw, hw->pdata->rxneg);
	nuc900_send_first(hw, hw->pdata->lsb);
	nuc900_set_sleep(hw, hw->pdata->sleep);
	nuc900_spi_setup_txbitlen(hw, hw->pdata->txbitlen);
	nuc900_spi_setup_txnum(hw, hw->pdata->txnum);
	nuc900_set_divider(hw);
	nuc900_enable_int(hw);
}