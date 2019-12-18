#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  sei_t ;
typedef  int /*<<< orphan*/  sei_msgtype_t ;
typedef  int /*<<< orphan*/  sei_message_t ;
typedef  int /*<<< orphan*/  libcaption_stauts_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_ERROR ; 
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 size_t _copy_to_rbsp (int*,size_t,int const*,size_t) ; 
 int /*<<< orphan*/  sei_init (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  sei_message_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* sei_message_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sei_message_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

libcaption_stauts_t sei_parse(sei_t* sei, const uint8_t* data, size_t size, double timestamp)
{
    sei_init(sei, timestamp);
    int ret = 0;

    // SEI may contain more than one payload
    while (1 < size) {
        size_t payloadType = 0;
        size_t payloadSize = 0;

        while (0 < size && 255 == (*data)) {
            payloadType += 255;
            ++data, --size;
        }

        if (0 == size) {
            return LIBCAPTION_ERROR;
        }

        payloadType += (*data);
        ++data, --size;

        while (0 < size && 255 == (*data)) {
            payloadSize += 255;
            ++data, --size;
        }

        if (0 == size) {
            return LIBCAPTION_ERROR;
        }

        payloadSize += (*data);
        ++data, --size;

        if (payloadSize) {
            sei_message_t* msg = sei_message_new((sei_msgtype_t)payloadType, 0, payloadSize);
            uint8_t* payloadData = sei_message_data(msg);
            size_t bytes = _copy_to_rbsp(payloadData, payloadSize, data, size);
            sei_message_append(sei, msg);

            if (bytes < payloadSize) {
                return LIBCAPTION_ERROR;
            }

            data += bytes;
            size -= bytes;
            ++ret;
        }
    }

    // There should be one trailing byte, 0x80. But really, we can just ignore that fact.
    return LIBCAPTION_OK;
}