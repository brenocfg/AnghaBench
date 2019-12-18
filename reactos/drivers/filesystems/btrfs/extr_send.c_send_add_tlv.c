#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_5__ {size_t datalen; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ send_context ;
struct TYPE_6__ {void* length; void* type; } ;
typedef  TYPE_2__ btrfs_send_tlv ;

/* Variables and functions */
 int /*<<< orphan*/  RtlCopyMemory (TYPE_2__*,void*,void*) ; 

__attribute__((used)) static void send_add_tlv(send_context* context, uint16_t type, void* data, uint16_t length) {
    btrfs_send_tlv* tlv = (btrfs_send_tlv*)&context->data[context->datalen];

    tlv->type = type;
    tlv->length = length;

    if (length > 0 && data)
        RtlCopyMemory(&tlv[1], data, length);

    context->datalen += sizeof(btrfs_send_tlv) + length;
}