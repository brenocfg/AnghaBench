#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int method_size; int strings_size; } ;
struct TYPE_8__ {TYPE_1__ header; TYPE_2__* methods; } ;
struct TYPE_7__ {int class_id; int name_id; } ;
typedef  TYPE_3__ RBinDexObj ;

/* Variables and functions */
 char* getstr (TYPE_3__*,int) ; 

__attribute__((used)) static char *dex_method_name(RBinDexObj *bin, int idx) {
	if (idx < 0 || idx >= bin->header.method_size) {
		return NULL;
	}
	int cid = bin->methods[idx].class_id;
	if (cid < 0 || cid >= bin->header.strings_size) {
		return NULL;
	}
	int tid = bin->methods[idx].name_id;
	if (tid < 0 || tid >= bin->header.strings_size) {
		return NULL;
	}
	return getstr (bin, tid);
}