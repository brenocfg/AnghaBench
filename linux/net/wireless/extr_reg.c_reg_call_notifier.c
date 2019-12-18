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
struct wiphy {int /*<<< orphan*/  (* reg_notifier ) (struct wiphy*,struct regulatory_request*) ;} ;
struct regulatory_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wiphy*,struct regulatory_request*) ; 

__attribute__((used)) static void reg_call_notifier(struct wiphy *wiphy,
			      struct regulatory_request *request)
{
	if (wiphy->reg_notifier)
		wiphy->reg_notifier(wiphy, request);
}