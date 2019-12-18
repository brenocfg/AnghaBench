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
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  datalen; } ;
typedef  TYPE_1__ send_context ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  char BTRFS_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_CMD_UTIMES ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_ATIME ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_CTIME ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_MTIME ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_PATH ; 
 int /*<<< orphan*/  send_add_tlv (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  send_command (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_command_finish (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void send_utimes_command(send_context* context, char* path, BTRFS_TIME* atime, BTRFS_TIME* mtime, BTRFS_TIME* ctime) {
    ULONG pos = context->datalen;

    send_command(context, BTRFS_SEND_CMD_UTIMES);

    send_add_tlv(context, BTRFS_SEND_TLV_PATH, path, path ? (uint16_t)strlen(path) : 0);
    send_add_tlv(context, BTRFS_SEND_TLV_ATIME, atime, sizeof(BTRFS_TIME));
    send_add_tlv(context, BTRFS_SEND_TLV_MTIME, mtime, sizeof(BTRFS_TIME));
    send_add_tlv(context, BTRFS_SEND_TLV_CTIME, ctime, sizeof(BTRFS_TIME));

    send_command_finish(context, pos);
}