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
typedef  int /*<<< orphan*/  u16 ;
struct xt_ct_target_info_v1 {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_CT_DEFAULT_ZONE_DIR ; 
 int /*<<< orphan*/  NF_CT_ZONE_DIR_ORIG ; 
 int /*<<< orphan*/  NF_CT_ZONE_DIR_REPL ; 
#define  XT_CT_ZONE_DIR_ORIG 129 
#define  XT_CT_ZONE_DIR_REPL 128 

__attribute__((used)) static u16 xt_ct_flags_to_dir(const struct xt_ct_target_info_v1 *info)
{
	switch (info->flags & (XT_CT_ZONE_DIR_ORIG |
			       XT_CT_ZONE_DIR_REPL)) {
	case XT_CT_ZONE_DIR_ORIG:
		return NF_CT_ZONE_DIR_ORIG;
	case XT_CT_ZONE_DIR_REPL:
		return NF_CT_ZONE_DIR_REPL;
	default:
		return NF_CT_DEFAULT_ZONE_DIR;
	}
}