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
struct fchs_s {scalar_t__ cat_info; } ;
typedef  enum fc_parse_status { ____Placeholder_fc_parse_status } fc_parse_status ;

/* Variables and functions */
 scalar_t__ FC_CAT_BA_ACC ; 
 scalar_t__ FC_CAT_BA_RJT ; 
 int FC_PARSE_FAILURE ; 
 int FC_PARSE_OK ; 

enum fc_parse_status
fc_abts_rsp_parse(struct fchs_s *fchs, int len)
{
	if ((fchs->cat_info == FC_CAT_BA_ACC)
	    || (fchs->cat_info == FC_CAT_BA_RJT))
		return FC_PARSE_OK;

	return FC_PARSE_FAILURE;
}