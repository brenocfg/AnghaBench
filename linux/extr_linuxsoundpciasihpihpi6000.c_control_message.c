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
typedef  void* u16 ;
struct hpi_response {void* error; void* specific_error; } ;
struct hpi_message {int function; } ;
struct hpi_hw_obj {int /*<<< orphan*/  p_cache; } ;
struct hpi_adapter_obj {int /*<<< orphan*/  has_control_cache; struct hpi_hw_obj* priv; } ;

/* Variables and functions */
#define  HPI_CONTROL_GET_INFO 130 
#define  HPI_CONTROL_GET_STATE 129 
#define  HPI_CONTROL_SET_STATE 128 
 void* HPI_ERROR_BACKEND_BASE ; 
 void* HPI_ERROR_CONTROL_CACHING ; 
 void* hpi6000_update_control_cache (struct hpi_adapter_obj*,struct hpi_message*) ; 
 int /*<<< orphan*/  hpi_check_control_cache (int /*<<< orphan*/ ,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  hpi_cmn_control_cache_sync_to_msg (int /*<<< orphan*/ ,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static void control_message(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;

	switch (phm->function) {
	case HPI_CONTROL_GET_STATE:
		if (pao->has_control_cache) {
			u16 err;
			err = hpi6000_update_control_cache(pao, phm);

			if (err) {
				if (err >= HPI_ERROR_BACKEND_BASE) {
					phr->error =
						HPI_ERROR_CONTROL_CACHING;
					phr->specific_error = err;
				} else {
					phr->error = err;
				}
				break;
			}

			if (hpi_check_control_cache(phw->p_cache, phm, phr))
				break;
		}
		hw_message(pao, phm, phr);
		break;
	case HPI_CONTROL_SET_STATE:
		hw_message(pao, phm, phr);
		hpi_cmn_control_cache_sync_to_msg(phw->p_cache, phm, phr);
		break;

	case HPI_CONTROL_GET_INFO:
	default:
		hw_message(pao, phm, phr);
		break;
	}
}