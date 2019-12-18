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
struct tep_record {int /*<<< orphan*/  data; } ;
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int parse_common_pc (struct tep_handle*,int /*<<< orphan*/ ) ; 

int tep_data_preempt_count(struct tep_handle *tep, struct tep_record *rec)
{
	return parse_common_pc(tep, rec->data);
}