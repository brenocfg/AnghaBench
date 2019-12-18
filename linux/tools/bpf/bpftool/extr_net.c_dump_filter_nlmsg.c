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
struct tcmsg {int dummy; } ;
struct nlattr {int dummy; } ;
struct bpf_filter_t {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  devname; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int do_filter_dump (struct tcmsg*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dump_filter_nlmsg(void *cookie, void *msg, struct nlattr **tb)
{
	const struct bpf_filter_t *filter_info = cookie;

	return do_filter_dump((struct tcmsg *)msg, tb, filter_info->kind,
			      filter_info->devname, filter_info->ifindex);
}