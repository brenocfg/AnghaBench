#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvenc_data {int /*<<< orphan*/  session; } ;
struct nv_texture {TYPE_2__* tex; scalar_t__ res; scalar_t__ mapped_res; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* nvEncUnregisterResource ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* nvEncUnmapInputResource ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_5__ {TYPE_1__* lpVtbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* Release ) (TYPE_2__*) ;} ;

/* Variables and functions */
 TYPE_3__ nv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

__attribute__((used)) static void nv_texture_free(struct nvenc_data *enc, struct nv_texture *nvtex)
{
	if (nvtex->res) {
		if (nvtex->mapped_res) {
			nv.nvEncUnmapInputResource(enc->session,
						   nvtex->mapped_res);
		}
		nv.nvEncUnregisterResource(enc->session, nvtex->res);
		nvtex->tex->lpVtbl->Release(nvtex->tex);
	}
}