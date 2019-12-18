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
struct TYPE_9__ {int /*<<< orphan*/  status; int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {TYPE_1__ response; } ;
struct TYPE_11__ {TYPE_2__ header; } ;
struct TYPE_12__ {TYPE_3__ message; } ;
typedef  TYPE_4__ protocol_binary_response_no_extras ;

/* Variables and functions */
 int allow_closed_read ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int hickup_thread_running ; 
 TYPE_4__* malloc (int) ; 
 scalar_t__ safe_recv_packet (TYPE_4__*,int) ; 
 int /*<<< orphan*/  validate_response_header (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *binary_hickup_recv_verification_thread(void *arg) {
    protocol_binary_response_no_extras *response = malloc(65*1024);
    if (response != NULL) {
        while (safe_recv_packet(response, 65*1024)) {
            /* Just validate the packet format */
            validate_response_header(response,
                                     response->message.header.response.opcode,
                                     response->message.header.response.status);
        }
        free(response);
    }
    hickup_thread_running = false;
    allow_closed_read = false;
    return NULL;
}