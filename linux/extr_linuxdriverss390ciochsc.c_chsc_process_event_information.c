#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {TYPE_4__ nt0_area; int /*<<< orphan*/  nt2_area; } ;
struct TYPE_6__ {int code; } ;
struct TYPE_5__ {int length; int code; } ;
struct chsc_sei {int nt; TYPE_3__ u; scalar_t__ ntsm; TYPE_2__ response; TYPE_1__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,int,...) ; 
 scalar_t__ chsc (struct chsc_sei*) ; 
 int /*<<< orphan*/  chsc_process_sei_nt0 (TYPE_4__*) ; 
 int /*<<< orphan*/  chsc_process_sei_nt2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct chsc_sei*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void chsc_process_event_information(struct chsc_sei *sei, u64 ntsm)
{
	static int ntsm_unsupported;

	while (true) {
		memset(sei, 0, sizeof(*sei));
		sei->request.length = 0x0010;
		sei->request.code = 0x000e;
		if (!ntsm_unsupported)
			sei->ntsm = ntsm;

		if (chsc(sei))
			break;

		if (sei->response.code != 0x0001) {
			CIO_CRW_EVENT(2, "chsc: sei failed (rc=%04x, ntsm=%llx)\n",
				      sei->response.code, sei->ntsm);

			if (sei->response.code == 3 && sei->ntsm) {
				/* Fallback for old firmware. */
				ntsm_unsupported = 1;
				continue;
			}
			break;
		}

		CIO_CRW_EVENT(2, "chsc: sei successful (nt=%d)\n", sei->nt);
		switch (sei->nt) {
		case 0:
			chsc_process_sei_nt0(&sei->u.nt0_area);
			break;
		case 2:
			chsc_process_sei_nt2(&sei->u.nt2_area);
			break;
		default:
			CIO_CRW_EVENT(2, "chsc: unhandled nt: %d\n", sei->nt);
			break;
		}

		if (!(sei->u.nt0_area.flags & 0x80))
			break;
	}
}