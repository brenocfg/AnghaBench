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
struct TYPE_3__ {int atxctl; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct daio_mgr_ctrl_blk {TYPE_2__ dirty; int /*<<< orphan*/ * txctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATXCTL_CD ; 
 int /*<<< orphan*/  ATXCTL_LIV ; 
 int /*<<< orphan*/  ATXCTL_NUC ; 
 int /*<<< orphan*/  ATXCTL_RAW ; 
 int /*<<< orphan*/  ATXCTL_RIV ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int daio_mgr_dao_init(void *blk, unsigned int idx, unsigned int conf)
{
	struct daio_mgr_ctrl_blk *ctl = blk;

	if (idx < 4) {
		/* S/PDIF output */
		switch ((conf & 0x7)) {
		case 1:
			set_field(&ctl->txctl[idx], ATXCTL_NUC, 0);
			break;
		case 2:
			set_field(&ctl->txctl[idx], ATXCTL_NUC, 1);
			break;
		case 4:
			set_field(&ctl->txctl[idx], ATXCTL_NUC, 2);
			break;
		case 8:
			set_field(&ctl->txctl[idx], ATXCTL_NUC, 3);
			break;
		default:
			break;
		}
		/* CDIF */
		set_field(&ctl->txctl[idx], ATXCTL_CD, (!(conf & 0x7)));
		/* Non-audio */
		set_field(&ctl->txctl[idx], ATXCTL_LIV, (conf >> 4) & 0x1);
		/* Non-audio */
		set_field(&ctl->txctl[idx], ATXCTL_RIV, (conf >> 4) & 0x1);
		set_field(&ctl->txctl[idx], ATXCTL_RAW,
			  ((conf >> 3) & 0x1) ? 0 : 0);
		ctl->dirty.bf.atxctl |= (0x1 << idx);
	} else {
		/* I2S output */
		/*idx %= 4; */
	}
	return 0;
}