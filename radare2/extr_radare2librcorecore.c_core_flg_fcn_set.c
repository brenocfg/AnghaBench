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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  RFlagItem ;
typedef  int /*<<< orphan*/  RFlag ;

/* Variables and functions */
 int /*<<< orphan*/  R_FLAGS_FS_FUNCTIONS ; 
 int /*<<< orphan*/ * r_flag_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_flag_space_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_flag_space_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RFlagItem *core_flg_fcn_set(RFlag *f, const char *name, ut64 addr, ut32 size) {
	r_flag_space_push (f, R_FLAGS_FS_FUNCTIONS);
	RFlagItem *res = r_flag_set (f, name, addr, size);
	r_flag_space_pop (f);
	return res;
}