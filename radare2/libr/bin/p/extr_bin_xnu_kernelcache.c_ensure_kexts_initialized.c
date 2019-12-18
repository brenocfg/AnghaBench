#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int kexts_initialized; int /*<<< orphan*/  kexts; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RKernelCacheObj ;

/* Variables and functions */
 int /*<<< orphan*/ * carve_kexts (TYPE_1__*) ; 
 int /*<<< orphan*/ * filter_kexts (TYPE_1__*) ; 
 int /*<<< orphan*/  r_kext_index_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ensure_kexts_initialized(RKernelCacheObj *obj) {
	if (obj->kexts_initialized) {
		return;
	}
	obj->kexts_initialized = true;

	RList *kexts = filter_kexts (obj);

	if (kexts && !r_list_length (kexts)) {
		r_list_free (kexts);
		kexts = NULL;
	}

	if (!kexts) {
		kexts = carve_kexts (obj);
	}

	obj->kexts = r_kext_index_new (kexts);
}