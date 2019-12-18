#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rtable_names; } ;
typedef  TYPE_1__ deparse_namespace ;
struct TYPE_5__ {int /*<<< orphan*/  namespaces; } ;
typedef  TYPE_2__ deparse_context ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
get_rtable_name(int rtindex, deparse_context *context)
{
	deparse_namespace *dpns = (deparse_namespace *) linitial(context->namespaces);

	Assert(rtindex > 0 && rtindex <= list_length(dpns->rtable_names));
	return (char *) list_nth(dpns->rtable_names, rtindex - 1);
}