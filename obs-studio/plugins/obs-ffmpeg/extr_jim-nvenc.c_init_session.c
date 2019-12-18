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
struct nvenc_data {int /*<<< orphan*/  session; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* nvEncOpenEncodeSessionEx ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  apiVersion; int /*<<< orphan*/  deviceType; int /*<<< orphan*/  device; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  NVENCAPI_VERSION ; 
 int /*<<< orphan*/  NV_ENC_DEVICE_TYPE_DIRECTX ; 
 int /*<<< orphan*/  NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS_VER ; 
 scalar_t__ NV_FAILED (int /*<<< orphan*/ ) ; 
 TYPE_3__ nv ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool init_session(struct nvenc_data *enc)
{
	NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS params = {
		NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS_VER};
	params.device = enc->device;
	params.deviceType = NV_ENC_DEVICE_TYPE_DIRECTX;
	params.apiVersion = NVENCAPI_VERSION;

	if (NV_FAILED(nv.nvEncOpenEncodeSessionEx(&params, &enc->session))) {
		return false;
	}
	return true;
}