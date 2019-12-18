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
struct TYPE_6__ {int method_size; } ;
struct TYPE_8__ {TYPE_2__* methods; TYPE_1__ header; } ;
struct TYPE_7__ {int /*<<< orphan*/  proto_id; } ;
typedef  TYPE_3__ RBinDexObj ;

/* Variables and functions */
 char* dex_get_proto (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *dex_method_signature(RBinDexObj *bin, int method_idx) {
	if (method_idx < 0 || method_idx >= bin->header.method_size) {
		return NULL;
	}
	return dex_get_proto (bin, bin->methods[method_idx].proto_id);
}