#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {int vmi_base_count; TYPE_12__* vmi_bases; scalar_t__ vmi_flags; int /*<<< orphan*/  name; scalar_t__ name_addr; scalar_t__ vtable_addr; } ;
typedef  TYPE_2__ vmi_class_type_info ;
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  base_class_type_info ;
struct TYPE_14__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* read_at ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_17__ {TYPE_1__ iob; } ;
struct TYPE_16__ {scalar_t__ word_size; TYPE_4__* anal; int /*<<< orphan*/  (* read_addr ) (TYPE_4__*,scalar_t__,scalar_t__*) ;} ;
struct TYPE_13__ {scalar_t__ flags; scalar_t__ base_class_addr; } ;
typedef  TYPE_3__ RVTableContext ;

/* Variables and functions */
 int NAME_BUF_SIZE ; 
 scalar_t__ UT64_MAX ; 
 TYPE_12__* calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int r_str_len_utf8 (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_4__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_4__*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static bool rtti_itanium_read_vmi_class_type_info (RVTableContext *context, ut64 addr, vmi_class_type_info *vmi_cti) {
	ut64 at;
	if (addr == UT64_MAX) {
		return false;
	}
	if (!context->read_addr (context->anal, addr, &at)) {
		return false;
	}
	vmi_cti->vtable_addr = at;
	addr += context->word_size;
	if (!context->read_addr (context->anal, addr, &at)) {
		return false;
	}
	vmi_cti->name_addr = at;
	ut8 buf[NAME_BUF_SIZE];
	if (!context->anal->iob.read_at (context->anal->iob.io, at, buf, sizeof(buf))) {
		return false;
	}
	size_t name_len = r_str_len_utf8 ((const char *)buf) + 1;
	vmi_cti->name = malloc (name_len);
	if (!vmi_cti->name) {
		return false;
	}
	memcpy (vmi_cti->name, buf, name_len);
	addr += context->word_size;
	if (!context->read_addr (context->anal, addr, &at)) {
		return false;
	}
	vmi_cti->vmi_flags = at;
	addr += 0x4;
	if (!context->read_addr (context->anal, addr, &at)) {
		return false;
	}
	if (at < 1 || at > 0xfffff) {
		eprintf ("Error reading vmi_base_count\n");
		return false;
	}
	vmi_cti->vmi_base_count = at;
	vmi_cti->vmi_bases = calloc (sizeof (base_class_type_info), vmi_cti->vmi_base_count);
	if (!vmi_cti->vmi_bases) {
		return false;
	}
	ut64 tmp_addr = addr + 0x4;

	int i;
	for (i = 0; i < vmi_cti->vmi_base_count; i++) {
		if (!context->read_addr (context->anal, tmp_addr, &at)) {
			return false;
		}
		vmi_cti->vmi_bases[i].base_class_addr = at;
		tmp_addr += context->word_size;
		if (!context->read_addr (context->anal, tmp_addr, &at)) {
			return false;
		}
		vmi_cti->vmi_bases[i].flags = at;
		tmp_addr += context->word_size;
	}
	return true;
}