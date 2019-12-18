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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  datalen; } ;
typedef  TYPE_1__ send_context ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_CMD_RMDIR ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_PATH ; 
 int /*<<< orphan*/  send_add_tlv (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_command (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_command_finish (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_rmdir_command(send_context* context, uint16_t pathlen, char* path) {
    ULONG pos = context->datalen;

    send_command(context, BTRFS_SEND_CMD_RMDIR);
    send_add_tlv(context, BTRFS_SEND_TLV_PATH, path, pathlen);
    send_command_finish(context, pos);
}