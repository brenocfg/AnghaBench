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
struct regulatory_request {int dummy; } ;

/* Variables and functions */
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  last_request ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct regulatory_request*) ; 
 int /*<<< orphan*/  reg_free_last_request () ; 

__attribute__((used)) static void reg_update_last_request(struct regulatory_request *request)
{
	struct regulatory_request *lr;

	lr = get_last_request();
	if (lr == request)
		return;

	reg_free_last_request();
	rcu_assign_pointer(last_request, request);
}