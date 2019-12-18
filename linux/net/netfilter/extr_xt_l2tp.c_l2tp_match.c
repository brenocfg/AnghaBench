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
struct xt_l2tp_info {int flags; scalar_t__ type; int version; scalar_t__ tid; scalar_t__ sid; } ;
struct l2tp_data {scalar_t__ type; int version; scalar_t__ tid; scalar_t__ sid; } ;

/* Variables and functions */
 int XT_L2TP_SID ; 
 int XT_L2TP_TID ; 
 int XT_L2TP_TYPE ; 
 scalar_t__ XT_L2TP_TYPE_CONTROL ; 
 scalar_t__ XT_L2TP_TYPE_DATA ; 
 int XT_L2TP_VERSION ; 

__attribute__((used)) static bool l2tp_match(const struct xt_l2tp_info *info, struct l2tp_data *data)
{
	if ((info->flags & XT_L2TP_TYPE) && (info->type != data->type))
		return false;

	if ((info->flags & XT_L2TP_VERSION) && (info->version != data->version))
		return false;

	/* Check tid only for L2TPv3 control or any L2TPv2 packets */
	if ((info->flags & XT_L2TP_TID) &&
	    ((data->type == XT_L2TP_TYPE_CONTROL) || (data->version == 2)) &&
	    (info->tid != data->tid))
		return false;

	/* Check sid only for L2TP data packets */
	if ((info->flags & XT_L2TP_SID) && (data->type == XT_L2TP_TYPE_DATA) &&
	    (info->sid != data->sid))
		return false;

	return true;
}