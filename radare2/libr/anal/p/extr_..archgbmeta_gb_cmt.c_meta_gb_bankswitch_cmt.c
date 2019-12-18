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
typedef  int ut64 ;
typedef  int ut16 ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_META_TYPE_COMMENT ; 
 int /*<<< orphan*/  r_meta_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 

void meta_gb_bankswitch_cmt(RAnal *a, ut64 addr, ut16 ldarg) {
	if(0x1fff <ldarg && ldarg < 0x4000 && addr < 0x4000)
		r_meta_set_string (a, R_META_TYPE_COMMENT, addr, "Bankswitch");
	if(0x6000 > ldarg && ldarg > 0x3fff)
		r_meta_set_string(a, R_META_TYPE_COMMENT, addr, "Ramswitch");
}