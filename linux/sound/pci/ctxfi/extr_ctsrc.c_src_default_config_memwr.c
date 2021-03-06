#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ctrl_blk; TYPE_1__* ops; struct hw* hw; } ;
struct src {TYPE_2__ rsc; } ;
struct hw {int /*<<< orphan*/  (* src_commit_write ) (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_clear_zbufs ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* src_set_pitch ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* src_set_ca ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* src_set_la ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* src_set_sa ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* src_set_cisz ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* src_set_ilsz ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_st ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_vo ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_rom ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_pm ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_wr ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* src_set_sf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_rsr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_bm ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* src_set_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* index ) (TYPE_2__*) ;int /*<<< orphan*/  (* master ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SRC_SF_S16 ; 
 int /*<<< orphan*/  SRC_STATE_OFF ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub17 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub18 (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int src_default_config_memwr(struct src *src)
{
	struct hw *hw = src->rsc.hw;

	hw->src_set_state(src->rsc.ctrl_blk, SRC_STATE_OFF);
	hw->src_set_bm(src->rsc.ctrl_blk, 1);
	hw->src_set_rsr(src->rsc.ctrl_blk, 0);
	hw->src_set_sf(src->rsc.ctrl_blk, SRC_SF_S16);
	hw->src_set_wr(src->rsc.ctrl_blk, 1);
	hw->src_set_pm(src->rsc.ctrl_blk, 0);
	hw->src_set_rom(src->rsc.ctrl_blk, 0);
	hw->src_set_vo(src->rsc.ctrl_blk, 0);
	hw->src_set_st(src->rsc.ctrl_blk, 0);
	hw->src_set_ilsz(src->rsc.ctrl_blk, 0);
	hw->src_set_cisz(src->rsc.ctrl_blk, 0x80);
	hw->src_set_sa(src->rsc.ctrl_blk, 0x0);
	hw->src_set_la(src->rsc.ctrl_blk, 0x1000);
	hw->src_set_ca(src->rsc.ctrl_blk, 0x80);
	hw->src_set_pitch(src->rsc.ctrl_blk, 0x1000000);
	hw->src_set_clear_zbufs(src->rsc.ctrl_blk, 1);

	src->rsc.ops->master(&src->rsc);
	hw->src_commit_write(hw, src->rsc.ops->index(&src->rsc),
						src->rsc.ctrl_blk);

	return 0;
}