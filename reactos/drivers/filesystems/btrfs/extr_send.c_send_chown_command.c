#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char uint64_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  datalen; } ;
typedef  TYPE_1__ send_context ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_CMD_CHOWN ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_GID ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_PATH ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_UID ; 
 int /*<<< orphan*/  send_add_tlv (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  send_command (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_command_finish (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void send_chown_command(send_context* context, char* path, uint64_t uid, uint64_t gid) {
    ULONG pos = context->datalen;

    send_command(context, BTRFS_SEND_CMD_CHOWN);

    send_add_tlv(context, BTRFS_SEND_TLV_PATH, path, path ? (uint16_t)strlen(path) : 0);
    send_add_tlv(context, BTRFS_SEND_TLV_UID, &uid, sizeof(uint64_t));
    send_add_tlv(context, BTRFS_SEND_TLV_GID, &gid, sizeof(uint64_t));

    send_command_finish(context, pos);
}