#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvenc_data {int /*<<< orphan*/  session; } ;
struct nv_bitstream {int /*<<< orphan*/  event; scalar_t__ ptr; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* nvEncUnregisterAsyncEvent ) (int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  (* nvEncDestroyBitstreamBuffer ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  completionEvent; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ NV_ENC_EVENT_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_ENC_EVENT_PARAMS_VER ; 
 TYPE_3__ nv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void nv_bitstream_free(struct nvenc_data *enc, struct nv_bitstream *bs)
{
	if (bs->ptr) {
		nv.nvEncDestroyBitstreamBuffer(enc->session, bs->ptr);

		NV_ENC_EVENT_PARAMS params = {NV_ENC_EVENT_PARAMS_VER};
		params.completionEvent = bs->event;
		nv.nvEncUnregisterAsyncEvent(enc->session, &params);
		CloseHandle(bs->event);
	}
}