#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ RParsedPointer ;
typedef  int /*<<< orphan*/  RKernelCacheObj ;

/* Variables and functions */
 int /*<<< orphan*/  r_parse_pointer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 p_ptr (ut64 decorated_addr, RKernelCacheObj *obj) {
	RParsedPointer ptr;
	r_parse_pointer (&ptr, decorated_addr, obj);
	return ptr.address;
}