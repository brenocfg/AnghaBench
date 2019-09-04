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
typedef  int /*<<< orphan*/  sei_message_t ;
typedef  int /*<<< orphan*/  cea708_t ;

/* Variables and functions */
 scalar_t__ LIBCAPTION_OK ; 
 int /*<<< orphan*/  cea708_dump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cea708_init (int /*<<< orphan*/ *,double) ; 
 scalar_t__ cea708_parse_h262 (int*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int* sei_message_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sei_message_next (int /*<<< orphan*/ *) ; 
 size_t sei_message_size (int /*<<< orphan*/ *) ; 
 scalar_t__ sei_message_type (int /*<<< orphan*/ *) ; 
 scalar_t__ sei_type_user_data_registered_itu_t_t35 ; 
 int /*<<< orphan*/  stderr ; 

void sei_dump_messages(sei_message_t* head, double timestamp)
{
    cea708_t cea708;
    sei_message_t* msg;
    cea708_init(&cea708, timestamp);

    for (msg = head; msg; msg = sei_message_next(msg)) {
        uint8_t* data = sei_message_data(msg);
        size_t size = sei_message_size(msg);
        fprintf(stderr, "-- Message %p\n-- Message Type: %d\n-- Message Size: %d\n", data, sei_message_type(msg), (int)size);

        while (size) {
            fprintf(stderr, "%02X ", *data);
            ++data;
            --size;
        }

        fprintf(stderr, "\n");

        if (sei_type_user_data_registered_itu_t_t35 == sei_message_type(msg)) {
            if (LIBCAPTION_OK != cea708_parse_h262(sei_message_data(msg), sei_message_size(msg), &cea708)) {
                fprintf(stderr, "cea708_parse error\n");
            } else {
                cea708_dump(&cea708);
            }
        }
    }
}