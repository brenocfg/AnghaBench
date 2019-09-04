#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wwn_t ;
struct fchs_s {int dummy; } ;
struct TYPE_2__ {int class_valid; scalar_t__ rxsz; } ;
struct fc_logi_s {int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; TYPE_1__ class3; } ;
typedef  enum fc_parse_status { ____Placeholder_fc_parse_status } fc_parse_status ;

/* Variables and functions */
 int FC_MIN_PDUSZ ; 
 int FC_PARSE_FAILURE ; 
 int FC_PARSE_OK ; 
 int be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  wwn_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum fc_parse_status
fc_pdisc_parse(struct fchs_s *fchs, wwn_t node_name, wwn_t port_name)
{
	struct fc_logi_s *pdisc = (struct fc_logi_s *) (fchs + 1);

	if (pdisc->class3.class_valid != 1)
		return FC_PARSE_FAILURE;

	if ((be16_to_cpu(pdisc->class3.rxsz) <
		(FC_MIN_PDUSZ - sizeof(struct fchs_s)))
	    || (pdisc->class3.rxsz == 0))
		return FC_PARSE_FAILURE;

	if (!wwn_is_equal(pdisc->port_name, port_name))
		return FC_PARSE_FAILURE;

	if (!wwn_is_equal(pdisc->node_name, node_name))
		return FC_PARSE_FAILURE;

	return FC_PARSE_OK;
}