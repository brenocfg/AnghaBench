#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct esas2r_request {scalar_t__ req_stat; TYPE_1__* vrq; } ;
struct esas2r_adapter {int /*<<< orphan*/  nvram_semaphore; int /*<<< orphan*/  flags; } ;
struct atto_vda_flash_req {int sub_func; } ;
struct TYPE_2__ {struct atto_vda_flash_req flash; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NVR_VALID ; 
 scalar_t__ RS_PENDING ; 
 scalar_t__ RS_SUCCESS ; 
#define  VDA_FLASH_BEGINW 131 
#define  VDA_FLASH_COMMIT 130 
#define  VDA_FLASH_READ 129 
#define  VDA_FLASH_WRITE 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_enable_heartbeat (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_nvram_validate (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esas2r_nvram_callback(struct esas2r_adapter *a,
				  struct esas2r_request *rq)
{
	struct atto_vda_flash_req *vrq = &rq->vrq->flash;

	if (rq->req_stat == RS_SUCCESS) {
		/* last request was successful.  see what to do now. */

		switch (vrq->sub_func) {
		case VDA_FLASH_BEGINW:
			vrq->sub_func = VDA_FLASH_WRITE;
			rq->req_stat = RS_PENDING;
			break;

		case VDA_FLASH_WRITE:
			vrq->sub_func = VDA_FLASH_COMMIT;
			rq->req_stat = RS_PENDING;
			break;

		case VDA_FLASH_READ:
			esas2r_nvram_validate(a);
			break;

		case VDA_FLASH_COMMIT:
		default:
			break;
		}
	}

	if (rq->req_stat != RS_PENDING) {
		/* update the NVRAM state */
		if (rq->req_stat == RS_SUCCESS)
			set_bit(AF_NVR_VALID, &a->flags);
		else
			clear_bit(AF_NVR_VALID, &a->flags);

		esas2r_enable_heartbeat(a);

		up(&a->nvram_semaphore);
	}
}