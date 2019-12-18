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
struct uda1380_priv {int /*<<< orphan*/  i2c; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int UDA1380_MVOL ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_master_recv (int /*<<< orphan*/ ,int*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 struct uda1380_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_is_active (struct snd_soc_component*) ; 
 int /*<<< orphan*/  uda1380_cache_dirty ; 
 int /*<<< orphan*/  uda1380_write_reg_cache (struct snd_soc_component*,unsigned int,unsigned int) ; 

__attribute__((used)) static int uda1380_write(struct snd_soc_component *component, unsigned int reg,
	unsigned int value)
{
	struct uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	u8 data[3];

	/* data is
	 *   data[0] is register offset
	 *   data[1] is MS byte
	 *   data[2] is LS byte
	 */
	data[0] = reg;
	data[1] = (value & 0xff00) >> 8;
	data[2] = value & 0x00ff;

	uda1380_write_reg_cache(component, reg, value);

	/* the interpolator & decimator regs must only be written when the
	 * codec DAI is active.
	 */
	if (!snd_soc_component_is_active(component) && (reg >= UDA1380_MVOL))
		return 0;
	pr_debug("uda1380: hw write %x val %x\n", reg, value);
	if (i2c_master_send(uda1380->i2c, data, 3) == 3) {
		unsigned int val;
		i2c_master_send(uda1380->i2c, data, 1);
		i2c_master_recv(uda1380->i2c, data, 2);
		val = (data[0]<<8) | data[1];
		if (val != value) {
			pr_debug("uda1380: READ BACK VAL %x\n",
					(data[0]<<8) | data[1]);
			return -EIO;
		}
		if (reg >= 0x10)
			clear_bit(reg - 0x10, &uda1380_cache_dirty);
		return 0;
	} else
		return -EIO;
}