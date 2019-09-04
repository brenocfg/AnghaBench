#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ add_cdb_len; } ;
struct TYPE_7__ {TYPE_2__ fcp_cmnd; } ;
struct TYPE_5__ {int /*<<< orphan*/  attr_n_length; } ;
struct TYPE_8__ {TYPE_3__ isp24; TYPE_1__ raw; } ;
struct atio_from_isp {TYPE_4__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCP_CMD_LENGTH_MIN ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void adjust_corrupted_atio(struct atio_from_isp *atio)
{
	atio->u.raw.attr_n_length = cpu_to_le16(FCP_CMD_LENGTH_MIN);
	atio->u.isp24.fcp_cmnd.add_cdb_len = 0;
}