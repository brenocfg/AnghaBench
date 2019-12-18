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
struct ubifs_info {TYPE_1__* dbg; } ;
struct TYPE_4__ {scalar_t__ chk_orph; } ;
struct TYPE_3__ {scalar_t__ chk_orph; } ;

/* Variables and functions */
 TYPE_2__ ubifs_dbg ; 

__attribute__((used)) static inline int dbg_is_chk_orph(const struct ubifs_info *c)
{
	return !!(ubifs_dbg.chk_orph || c->dbg->chk_orph);
}