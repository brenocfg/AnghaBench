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
typedef  scalar_t__ u32 ;
struct ath_softc {scalar_t__ mem; int /*<<< orphan*/  sc_serial_rw; } ;
struct TYPE_2__ {scalar_t__ serialize_regmode; } ;
struct ath_hw {TYPE_1__ config; } ;
struct ath_common {scalar_t__ priv; } ;

/* Variables and functions */
 int NR_CPUS ; 
 scalar_t__ SER_REG_MODE_ON ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ath9k_iowrite32(void *hw_priv, u32 val, u32 reg_offset)
{
	struct ath_hw *ah = hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_softc *sc = (struct ath_softc *) common->priv;

	if (NR_CPUS > 1 && ah->config.serialize_regmode == SER_REG_MODE_ON) {
		unsigned long flags;
		spin_lock_irqsave(&sc->sc_serial_rw, flags);
		iowrite32(val, sc->mem + reg_offset);
		spin_unlock_irqrestore(&sc->sc_serial_rw, flags);
	} else
		iowrite32(val, sc->mem + reg_offset);
}