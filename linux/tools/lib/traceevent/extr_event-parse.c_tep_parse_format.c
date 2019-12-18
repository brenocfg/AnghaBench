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
struct tep_handle {int dummy; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int __parse_event (struct tep_handle*,struct tep_event**,char const*,unsigned long,char const*) ; 

enum tep_errno tep_parse_format(struct tep_handle *tep,
				struct tep_event **eventp,
				const char *buf,
				unsigned long size, const char *sys)
{
	return __parse_event(tep, eventp, buf, size, sys);
}