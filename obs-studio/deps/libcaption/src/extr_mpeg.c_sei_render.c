#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ sei_t ;
typedef  int /*<<< orphan*/  sei_message_t ;

/* Variables and functions */
 size_t _copy_from_rbsp (int*,int*,int) ; 
 int* sei_message_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sei_message_head (TYPE_1__*) ; 
 int /*<<< orphan*/ * sei_message_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sei_message_size (int /*<<< orphan*/ *) ; 
 int sei_message_type (int /*<<< orphan*/ *) ; 

size_t sei_render(sei_t* sei, uint8_t* data)
{
    if (!sei || !sei->head) {
        return 0;
    }

    size_t escaped_size, size = 2; // nalu_type + stop bit
    sei_message_t* msg;
    (*data) = 6;
    ++data;

    for (msg = sei_message_head(sei); msg; msg = sei_message_next(msg)) {
        int payloadType = sei_message_type(msg);
        int payloadSize = (int)sei_message_size(msg);
        uint8_t* payloadData = sei_message_data(msg);

        while (255 <= payloadType) {
            (*data) = 255;
            ++data;
            ++size;
            payloadType -= 255;
        }

        (*data) = payloadType;
        ++data;
        ++size;

        while (255 <= payloadSize) {
            (*data) = 255;
            ++data;
            ++size;
            payloadSize -= 255;
        }

        (*data) = payloadSize;
        ++data;
        ++size;

        if (0 >= (escaped_size = _copy_from_rbsp(data, payloadData, payloadSize))) {
            return 0;
        }

        data += escaped_size;
        size += escaped_size;
    }

    // write stop bit and return
    (*data) = 0x80;
    return size;
}