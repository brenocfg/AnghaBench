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
struct TYPE_5__ {int /*<<< orphan*/  (* nvEncGetEncodeCaps ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  capsToQuery; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ NV_ENC_CAPS_PARAM ;
typedef  int /*<<< orphan*/  NV_ENC_CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ENC_CAPS_PARAM_VER ; 
 int /*<<< orphan*/  NV_ENC_CODEC_H264_GUID ; 
 TYPE_3__ nv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 

__attribute__((used)) static inline int nv_get_cap(struct nvenc_data *enc, NV_ENC_CAPS cap)
{
	if (!enc->session)
		return 0;

	NV_ENC_CAPS_PARAM param = {NV_ENC_CAPS_PARAM_VER};
	int v;

	param.capsToQuery = cap;
	nv.nvEncGetEncodeCaps(enc->session, NV_ENC_CODEC_H264_GUID, &param, &v);
	return v;
}