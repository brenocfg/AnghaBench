#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {size_t datalen; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ send_context ;
struct TYPE_5__ {size_t length; int /*<<< orphan*/  csum; } ;
typedef  TYPE_2__ btrfs_send_command ;
typedef  size_t ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  calc_crc32c (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void send_command_finish(send_context* context, ULONG pos) {
    btrfs_send_command* bsc = (btrfs_send_command*)&context->data[pos];

    bsc->length = context->datalen - pos - sizeof(btrfs_send_command);
    bsc->csum = calc_crc32c(0, (uint8_t*)bsc, context->datalen - pos);
}