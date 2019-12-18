#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
struct TYPE_4__ {scalar_t__ Low; scalar_t__ High; } ;
typedef  TYPE_1__ ut128 ;
typedef  int /*<<< orphan*/  PCONTEXT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int CONTEXT_ALL ; 
 int CONTEXT_XSTATE ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetThreadContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSTATE_AVX ; 
 int /*<<< orphan*/  XSTATE_LEGACY_SSE ; 
 int XSTATE_MASK_AVX ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int w32_GetEnabledXStateFeatures () ; 
 scalar_t__ w32_GetXStateFeaturesMask (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ w32_InitializeContext (void*,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ w32_LocateXStateFeature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  w32_SetXStateFeaturesMask (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __get_avx(HANDLE th, ut128 xmm[16], ut128 ymm[16]) {
	int nregs = 0, index = 0;
	DWORD ctxsize = 0;
	DWORD featurelen = 0;
	ut64 featuremask = 0;
	ut128 *newxmm = NULL;
	ut128 *newymm = NULL;
	void *buffer = NULL;
	PCONTEXT ctx;
	if (!w32_GetEnabledXStateFeatures) {
		return 0;
	}
	// Check for AVX extension
	featuremask = w32_GetEnabledXStateFeatures ();
	if ((featuremask & XSTATE_MASK_AVX) == 0) {
		return 0;
	}
	if ((w32_InitializeContext (NULL, CONTEXT_ALL | CONTEXT_XSTATE, NULL, &ctxsize)) || (GetLastError () != ERROR_INSUFFICIENT_BUFFER)) {
		return 0;
	}
	buffer = malloc (ctxsize);
	if (!buffer) {
		return 0;
	}
	if (!w32_InitializeContext (buffer, CONTEXT_ALL | CONTEXT_XSTATE, &ctx, &ctxsize)) {
		goto err_get_avx;
	}
	if (!w32_SetXStateFeaturesMask (ctx, XSTATE_MASK_AVX)) {
		goto err_get_avx;
	}
	// TODO: Use __get_thread_context
	if (!GetThreadContext (th, ctx)) {
		goto err_get_avx;
	}
	if (w32_GetXStateFeaturesMask (ctx, &featuremask)) {
		goto err_get_avx;
	}
	newxmm = (ut128 *)w32_LocateXStateFeature (ctx, XSTATE_LEGACY_SSE, &featurelen);
		nregs = featurelen / sizeof(*newxmm);
	for (index = 0; index < nregs; index++) {
		ymm[index].High = 0;
		xmm[index].High = 0;
		ymm[index].Low = 0;
		xmm[index].Low = 0;
	}
	if (newxmm != NULL) {
		for (index = 0; index < nregs; index++) {
			xmm[index].High = newxmm[index].High;
			xmm[index].Low = newxmm[index].Low;
		}
	}
	if ((featuremask & XSTATE_MASK_AVX) != 0) {
		// check for AVX initialization and get the pointer.
		newymm = (ut128 *)w32_LocateXStateFeature (ctx, XSTATE_AVX, NULL);
		if (!newymm) {
			goto err_get_avx;
		}
		for (index = 0; index < nregs; index++) {
			ymm[index].High = newymm[index].High;
			ymm[index].Low = newymm[index].Low;
		}
	}
err_get_avx:
	free (buffer);
	return nregs;
}