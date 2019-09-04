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
struct tcindex_filter_result {int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_TCINDEX_ACT ; 
 int /*<<< orphan*/  TCA_TCINDEX_POLICE ; 
 int /*<<< orphan*/  memset (struct tcindex_filter_result*,int /*<<< orphan*/ ,int) ; 
 int tcf_exts_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcindex_filter_result_init(struct tcindex_filter_result *r)
{
	memset(r, 0, sizeof(*r));
	return tcf_exts_init(&r->exts, TCA_TCINDEX_ACT, TCA_TCINDEX_POLICE);
}