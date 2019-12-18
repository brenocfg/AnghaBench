#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct espconn {int dummy; } ;
typedef  scalar_t__ sint8 ;
typedef  scalar_t__ sint16 ;
typedef  int netconn_event ;
struct TYPE_5__ {int write_flag; scalar_t__ err; scalar_t__ cntr; int /*<<< orphan*/ * ptrbuf; } ;
struct TYPE_6__ {struct espconn* pespconn; struct espconn* preverse; TYPE_1__ pcommon; scalar_t__ hs_status; } ;
typedef  TYPE_2__ espconn_msg ;

/* Variables and functions */
 int /*<<< orphan*/  ESPCONN_EVENT_CLOSED (struct espconn*) ; 
 int /*<<< orphan*/  ESPCONN_EVENT_ERROR (struct espconn*,scalar_t__) ; 
 scalar_t__ ESPCONN_OK ; 
#define  NETCONN_EVENT_CLOSE 129 
#define  NETCONN_EVENT_ERROR 128 
 int /*<<< orphan*/  espconn_kill_oldest_pcb () ; 
 int /*<<< orphan*/  lwIP_ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  os_free (TYPE_2__*) ; 

__attribute__((used)) static void espconn_close_internal(void *arg, netconn_event event_type)
{
	espconn_msg *pssl_recon = arg;
    struct espconn *espconn = NULL;
    sint8 ssl_reerr = 0;
    sint16 hs_status = 0;
    lwIP_ASSERT(pssl_recon);

	espconn = pssl_recon->preverse;
	ssl_reerr = pssl_recon->pcommon.err;
	hs_status = pssl_recon->hs_status;
	if (espconn != NULL) {
		//clear pcommon parameters.
		pssl_recon->pcommon.write_flag = false;
		pssl_recon->pcommon.ptrbuf = NULL;
		pssl_recon->pcommon.cntr = 0;
		pssl_recon->pcommon.err  = 0;
		espconn = pssl_recon->preverse;
	} else {
		espconn = pssl_recon->pespconn;
		os_free(pssl_recon);
		pssl_recon = NULL;
	}

	espconn_kill_oldest_pcb();
	switch (event_type){
		case NETCONN_EVENT_ERROR:
			if (hs_status == ESPCONN_OK)
				ESPCONN_EVENT_ERROR(espconn, ssl_reerr);
			else
				ESPCONN_EVENT_ERROR(espconn, hs_status);
			break;
		case NETCONN_EVENT_CLOSE:
			if (hs_status == ESPCONN_OK)
				ESPCONN_EVENT_CLOSED(espconn);
			else
				ESPCONN_EVENT_ERROR(espconn, hs_status);
			break;
		default:
			break;
	}
}