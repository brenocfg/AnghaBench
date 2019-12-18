#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_endpoint_callback_parameter {scalar_t__ received_bytes; } ;
struct TYPE_3__ {scalar_t__ wLength; } ;
struct TYPE_4__ {scalar_t__ payload_size; scalar_t__ payload; int /*<<< orphan*/  (* over_under_run ) () ;TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDD_EPCTRL_STALL_REQ ; 
 scalar_t__ USB_DEVICE_EP_CTRL_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  udd_ctrl_buffer ; 
 scalar_t__ udd_ctrl_payload_nb_trans ; 
 scalar_t__ udd_ctrl_prev_payload_nb_trans ; 
 int /*<<< orphan*/  udd_ctrl_send_zlp_in () ; 
 int /*<<< orphan*/  udd_ep_control_state ; 
 int /*<<< orphan*/  udd_ep_set_halt (int /*<<< orphan*/ ) ; 
 TYPE_2__ udd_g_ctrlreq ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_endpoint_read_buffer_job (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void udd_ctrl_out_received(void *pointer) {
    struct usb_endpoint_callback_parameter *ep_callback_para = (struct usb_endpoint_callback_parameter *)pointer;

    uint16_t nb_data;
    nb_data = ep_callback_para->received_bytes; /* Read data received during OUT phase */

    if (udd_g_ctrlreq.payload_size < (udd_ctrl_payload_nb_trans + nb_data)) {
        /* Payload buffer too small */
        nb_data = udd_g_ctrlreq.payload_size - udd_ctrl_payload_nb_trans;
    }

    memcpy((uint8_t *)(udd_g_ctrlreq.payload + udd_ctrl_payload_nb_trans), udd_ctrl_buffer, nb_data);
    udd_ctrl_payload_nb_trans += nb_data;

    if ((USB_DEVICE_EP_CTRL_SIZE != nb_data) || (udd_g_ctrlreq.req.wLength <= (udd_ctrl_prev_payload_nb_trans + udd_ctrl_payload_nb_trans))) {
        /* End of reception because it is a short packet
         * or all data are transferred */

        /* Before send ZLP, call intermediate callback
         * in case of data receive generate a stall */
        udd_g_ctrlreq.payload_size = udd_ctrl_payload_nb_trans;
        if (NULL != udd_g_ctrlreq.over_under_run) {
            if (!udd_g_ctrlreq.over_under_run()) {
                /* Stall ZLP */
                udd_ep_control_state = UDD_EPCTRL_STALL_REQ;
                /* Stall all packets on IN & OUT control endpoint */
                udd_ep_set_halt(0);
                /* Ack reception of OUT to replace NAK by a STALL */
                return;
            }
        }
        /* Send IN ZLP to ACK setup request */
        udd_ctrl_send_zlp_in();
        return;
    }

    if (udd_g_ctrlreq.payload_size == udd_ctrl_payload_nb_trans) {
        /* Overrun then request a new payload buffer */
        if (!udd_g_ctrlreq.over_under_run) {
            /* No callback available to request a new payload buffer
             * Stall ZLP */
            udd_ep_control_state = UDD_EPCTRL_STALL_REQ;
            /* Stall all packets on IN & OUT control endpoint */
            udd_ep_set_halt(0);
            return;
        }
        if (!udd_g_ctrlreq.over_under_run()) {
            /* No new payload buffer delivered
             * Stall ZLP */
            udd_ep_control_state = UDD_EPCTRL_STALL_REQ;
            /* Stall all packets on IN & OUT control endpoint */
            udd_ep_set_halt(0);
            return;
        }
        /* New payload buffer available
         * Update number of total data received */
        udd_ctrl_prev_payload_nb_trans += udd_ctrl_payload_nb_trans;

        /* Reinitialize reception on payload buffer */
        udd_ctrl_payload_nb_trans = 0;
    }
    usb_device_endpoint_read_buffer_job(&usb_device, 0, udd_ctrl_buffer, USB_DEVICE_EP_CTRL_SIZE);
}