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
typedef  int /*<<< orphan*/  device_extension ;
struct TYPE_5__ {int cache_loaded; } ;
typedef  TYPE_1__ chunk ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  load_free_space_cache (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protect_superblocks (TYPE_1__*) ; 

NTSTATUS load_cache_chunk(device_extension* Vcb, chunk* c, PIRP Irp) {
    NTSTATUS Status;

    if (c->cache_loaded)
        return STATUS_SUCCESS;

    Status = load_free_space_cache(Vcb, c, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("load_free_space_cache returned %08x\n", Status);
        return Status;
    }

    protect_superblocks(c);

    c->cache_loaded = true;

    return STATUS_SUCCESS;
}