#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int averageBitRate; int maxBitRate; } ;
struct TYPE_7__ {TYPE_1__ rcParams; } ;
struct nvenc_data {int /*<<< orphan*/  session; int /*<<< orphan*/  params; TYPE_2__ config; scalar_t__ can_change_bitrate; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* nvEncReconfigureEncoder ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_8__ {int resetEncoder; int forceIDR; int /*<<< orphan*/  reInitEncodeParams; int /*<<< orphan*/  version; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ NV_ENC_RECONFIGURE_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ENC_RECONFIGURE_PARAMS_VER ; 
 scalar_t__ NV_FAILED (int /*<<< orphan*/ ) ; 
 TYPE_5__ nv ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static bool nvenc_update(void *data, obs_data_t *settings)
{
	struct nvenc_data *enc = data;

	/* Only support reconfiguration of CBR bitrate */
	if (enc->can_change_bitrate) {
		int bitrate = (int)obs_data_get_int(settings, "bitrate");

		enc->config.rcParams.averageBitRate = bitrate * 1000;
		enc->config.rcParams.maxBitRate = bitrate * 1000;

		NV_ENC_RECONFIGURE_PARAMS params = {0};
		params.version = NV_ENC_RECONFIGURE_PARAMS_VER;
		params.reInitEncodeParams = enc->params;
		params.resetEncoder = 1;
		params.forceIDR = 1;

		if (NV_FAILED(nv.nvEncReconfigureEncoder(enc->session,
							 &params))) {
			return false;
		}
	}

	return true;
}