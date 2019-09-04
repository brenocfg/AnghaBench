#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_9__ {scalar_t__ name; int /*<<< orphan*/  spare; int /*<<< orphan*/  vtable_addr; } ;
typedef  TYPE_2__ rtti_type_descriptor ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* read_at ) (int /*<<< orphan*/ ,scalar_t__,char*,int) ;} ;
struct TYPE_11__ {TYPE_1__ iob; } ;
struct TYPE_10__ {int word_size; TYPE_4__* anal; int /*<<< orphan*/  (* read_addr ) (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ RVTableContext ;

/* Variables and functions */
 int NAME_BUF_SIZE ; 
 scalar_t__ UT64_MAX ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 

__attribute__((used)) static bool rtti_msvc_read_type_descriptor(RVTableContext *context, ut64 addr, rtti_type_descriptor *td) {
	if (addr == UT64_MAX) {
		return false;
	}

	if (!context->read_addr (context->anal, addr, &td->vtable_addr)) {
		return false;
	}
	if (!context->read_addr (context->anal, addr + context->word_size, &td->spare)) {
		return false;
	}

	ut64 nameAddr = addr + 2 * context->word_size;
	ut8 buf[NAME_BUF_SIZE];
	ut64 bufOffset = 0;
	size_t nameLen = 0;
	bool endFound = false;
	bool endInvalid = false;
	while (1) {
		context->anal->iob.read_at (context->anal->iob.io, nameAddr + bufOffset, buf, sizeof (buf));
		int i;
		for (i=0; i<sizeof (buf); i++) {
			if (buf[i] == '\0') {
				endFound = true;
				break;
			}
			if (buf[i] == 0xff) {
				endInvalid = true;
				break;
			}
			nameLen++;
		}
		if (endFound || endInvalid) {
			break;
		}
		bufOffset += sizeof (buf);
	}

	if (endInvalid) {
		return false;
	}

	td->name = malloc (nameLen + 1);
	if (!td->name) {
		return false;
	}

	if (bufOffset == 0) {
		memcpy (td->name, buf, nameLen + 1);
	} else {
		context->anal->iob.read_at (context->anal->iob.io, nameAddr,
									(ut8 *)td->name, (int) (nameLen + 1));
	}

	return true;
}