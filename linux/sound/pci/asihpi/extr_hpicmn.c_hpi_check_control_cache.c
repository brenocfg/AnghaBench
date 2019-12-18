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
struct hpi_response {scalar_t__ version; scalar_t__ specific_error; scalar_t__ error; } ;
struct hpi_message {int /*<<< orphan*/  adapter_index; int /*<<< orphan*/  obj_index; } ;
struct hpi_control_cache_single {int dummy; } ;
struct hpi_control_cache_info {int dummy; } ;
struct hpi_control_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  find_control (int /*<<< orphan*/ ,struct hpi_control_cache*,struct hpi_control_cache_info**) ; 
 short hpi_check_control_cache_single (struct hpi_control_cache_single*,struct hpi_message*,struct hpi_response*) ; 

short hpi_check_control_cache(struct hpi_control_cache *p_cache,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_control_cache_info *pI;

	if (!find_control(phm->obj_index, p_cache, &pI)) {
		HPI_DEBUG_LOG(VERBOSE,
			"HPICMN find_control() failed for adap %d\n",
			phm->adapter_index);
		return 0;
	}

	phr->error = 0;
	phr->specific_error = 0;
	phr->version = 0;

	return hpi_check_control_cache_single((struct hpi_control_cache_single
			*)pI, phm, phr);
}