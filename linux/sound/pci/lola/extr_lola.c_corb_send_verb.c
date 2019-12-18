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
struct TYPE_4__ {int cmds; } ;
struct TYPE_3__ {int wp; void** buf; } ;
struct lola {unsigned int last_cmd_nid; unsigned int last_verb; unsigned int last_data; unsigned int last_extdata; int /*<<< orphan*/  reg_lock; TYPE_2__ rirb; TYPE_1__ corb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR0 ; 
 int /*<<< orphan*/  CORBWP ; 
 int EIO ; 
 int LOLA_CORB_ENTRIES ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  lola_writew (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int corb_send_verb(struct lola *chip, unsigned int nid,
			  unsigned int verb, unsigned int data,
			  unsigned int extdata)
{
	unsigned long flags;
	int ret = -EIO;

	chip->last_cmd_nid = nid;
	chip->last_verb = verb;
	chip->last_data = data;
	chip->last_extdata = extdata;
	data |= (nid << 20) | (verb << 8);

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (chip->rirb.cmds < LOLA_CORB_ENTRIES - 1) {
		unsigned int wp = chip->corb.wp + 1;
		wp %= LOLA_CORB_ENTRIES;
		chip->corb.wp = wp;
		chip->corb.buf[wp * 2] = cpu_to_le32(data);
		chip->corb.buf[wp * 2 + 1] = cpu_to_le32(extdata);
		lola_writew(chip, BAR0, CORBWP, wp);
		chip->rirb.cmds++;
		smp_wmb();
		ret = 0;
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return ret;
}