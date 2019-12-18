#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_20__ {TYPE_5__* parent; int /*<<< orphan*/  datalen; } ;
typedef  TYPE_6__ send_context ;
struct TYPE_17__ {scalar_t__ rtransid; int /*<<< orphan*/  ctransid; int /*<<< orphan*/  received_uuid; int /*<<< orphan*/  uuid; } ;
struct TYPE_21__ {TYPE_3__ root_item; } ;
typedef  TYPE_7__ root ;
struct TYPE_22__ {TYPE_2__* dc; } ;
typedef  TYPE_8__ file_ref ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_18__ {scalar_t__ rtransid; int /*<<< orphan*/  ctransid; int /*<<< orphan*/  received_uuid; int /*<<< orphan*/  uuid; } ;
struct TYPE_19__ {TYPE_4__ root_item; } ;
struct TYPE_15__ {int Length; int /*<<< orphan*/ * Buffer; } ;
struct TYPE_16__ {TYPE_1__ utf8; } ;
typedef  int /*<<< orphan*/  BTRFS_UUID ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_CMD_SNAPSHOT ; 
 int /*<<< orphan*/  BTRFS_SEND_CMD_SUBVOL ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_CLONE_CTRANSID ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_CLONE_UUID ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_PATH ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_TRANSID ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_UUID ; 
 int /*<<< orphan*/  send_add_tlv (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_command (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_command_finish (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_subvol_header(send_context* context, root* r, file_ref* fr) {
    ULONG pos = context->datalen;

    send_command(context, context->parent ? BTRFS_SEND_CMD_SNAPSHOT : BTRFS_SEND_CMD_SUBVOL);

    send_add_tlv(context, BTRFS_SEND_TLV_PATH, fr->dc->utf8.Buffer, fr->dc->utf8.Length);

    send_add_tlv(context, BTRFS_SEND_TLV_UUID, r->root_item.rtransid == 0 ? &r->root_item.uuid : &r->root_item.received_uuid, sizeof(BTRFS_UUID));
    send_add_tlv(context, BTRFS_SEND_TLV_TRANSID, &r->root_item.ctransid, sizeof(uint64_t));

    if (context->parent) {
        send_add_tlv(context, BTRFS_SEND_TLV_CLONE_UUID,
                     context->parent->root_item.rtransid == 0 ? &context->parent->root_item.uuid : &context->parent->root_item.received_uuid, sizeof(BTRFS_UUID));
        send_add_tlv(context, BTRFS_SEND_TLV_CLONE_CTRANSID, &context->parent->root_item.ctransid, sizeof(uint64_t));
    }

    send_command_finish(context, pos);
}