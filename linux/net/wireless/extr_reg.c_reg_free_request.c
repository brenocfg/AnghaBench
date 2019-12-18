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
 struct regulatory_request core_request_world ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  kfree (struct regulatory_request*) ; 

__attribute__((used)) static void reg_free_request(struct regulatory_request *request)
{
	if (request == &core_request_world)
		return;

	if (request != get_last_request())
		kfree(request);
}