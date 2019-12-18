#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {TYPE_1__* item; } ;
typedef  TYPE_2__ traverse_ptr ;
struct TYPE_11__ {scalar_t__ parent; int /*<<< orphan*/  Vcb; scalar_t__ root; } ;
typedef  TYPE_3__ send_context ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_12__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  obj_type; int /*<<< orphan*/  obj_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__ KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SUBVOL_ROOT_INODE ; 
 int /*<<< orphan*/  TYPE_DIR_ITEM ; 
 int /*<<< orphan*/  calc_crc32c (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_item (int /*<<< orphan*/ ,scalar_t__,TYPE_2__*,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keycmp (TYPE_4__,int /*<<< orphan*/ ) ; 
 char* uint64_to_char (scalar_t__,char*) ; 

__attribute__((used)) static NTSTATUS get_orphan_name(send_context* context, uint64_t inode, uint64_t generation, char* name) {
    char *ptr, *ptr2;
    uint64_t index = 0;
    KEY searchkey;

    name[0] = 'o';

    ptr = uint64_to_char(inode, &name[1]);
    *ptr = '-'; ptr++;
    ptr = uint64_to_char(generation, ptr);
    *ptr = '-'; ptr++;
    ptr2 = ptr;

    searchkey.obj_id = SUBVOL_ROOT_INODE;
    searchkey.obj_type = TYPE_DIR_ITEM;

    do {
        NTSTATUS Status;
        traverse_ptr tp;

        ptr = uint64_to_char(index, ptr);
        *ptr = 0;

        searchkey.offset = calc_crc32c(0xfffffffe, (uint8_t*)name, (ULONG)(ptr - name));

        Status = find_item(context->Vcb, context->root, &tp, &searchkey, false, NULL);
        if (!NT_SUCCESS(Status)) {
            ERR("find_item returned %08x\n", Status);
            return Status;
        }

        if (!keycmp(searchkey, tp.item->key))
            goto cont;

        if (context->parent) {
            Status = find_item(context->Vcb, context->parent, &tp, &searchkey, false, NULL);
            if (!NT_SUCCESS(Status)) {
                ERR("find_item returned %08x\n", Status);
                return Status;
            }

            if (!keycmp(searchkey, tp.item->key))
                goto cont;
        }

        return STATUS_SUCCESS;

cont:
        index++;
        ptr = ptr2;
    } while (true);
}