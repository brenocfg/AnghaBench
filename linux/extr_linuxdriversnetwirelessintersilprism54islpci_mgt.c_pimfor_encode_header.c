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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int operation; void* length; void* oid; scalar_t__ flags; int /*<<< orphan*/  device_id; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ pimfor_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIMFOR_DEV_ID_MHLI_MIB ; 
 int /*<<< orphan*/  PIMFOR_VERSION ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pimfor_encode_header(int operation, u32 oid, u32 length, pimfor_header_t *h)
{
	h->version = PIMFOR_VERSION;
	h->operation = operation;
	h->device_id = PIMFOR_DEV_ID_MHLI_MIB;
	h->flags = 0;
	h->oid = cpu_to_be32(oid);
	h->length = cpu_to_be32(length);
}