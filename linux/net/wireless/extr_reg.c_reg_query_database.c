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
struct regulatory_request {int /*<<< orphan*/  alpha2; } ;

/* Variables and functions */
 scalar_t__ call_crda (int /*<<< orphan*/ ) ; 
 scalar_t__ query_regdb_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reg_query_database(struct regulatory_request *request)
{
	if (query_regdb_file(request->alpha2) == 0)
		return true;

	if (call_crda(request->alpha2) == 0)
		return true;

	return false;
}