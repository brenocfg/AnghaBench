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
typedef  int u8 ;
struct rp5c01_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int RP5C01_MODE ; 
 int RP5C01_MODE_MODE01 ; 
 int RP5C01_MODE_RAM_BLOCK10 ; 
 int RP5C01_MODE_RAM_BLOCK11 ; 
 int RP5C01_MODE_TIMER_EN ; 
 int /*<<< orphan*/  rp5c01_write (struct rp5c01_priv*,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rp5c01_nvram_write(void *_priv, unsigned int pos, void *val,
			      size_t bytes)
{
	struct rp5c01_priv *priv = _priv;
	u8 *buf = val;

	spin_lock_irq(&priv->lock);

	for (; bytes; bytes--) {
		u8 data = *buf++;

		rp5c01_write(priv,
			     RP5C01_MODE_TIMER_EN | RP5C01_MODE_RAM_BLOCK10,
			     RP5C01_MODE);
		rp5c01_write(priv, data >> 4, pos);
		rp5c01_write(priv,
			     RP5C01_MODE_TIMER_EN | RP5C01_MODE_RAM_BLOCK11,
			     RP5C01_MODE);
		rp5c01_write(priv, data & 0xf, pos++);
		rp5c01_write(priv, RP5C01_MODE_TIMER_EN | RP5C01_MODE_MODE01,
			     RP5C01_MODE);
	}

	spin_unlock_irq(&priv->lock);
	return 0;
}