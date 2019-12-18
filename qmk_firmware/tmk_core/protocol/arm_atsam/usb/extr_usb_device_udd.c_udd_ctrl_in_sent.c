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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ wLength; } ;
struct TYPE_4__ {scalar_t__ payload_size; scalar_t__ payload; int /*<<< orphan*/  (* over_under_run ) () ;TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP ; 
 scalar_t__ USB_DEVICE_EP_CTRL_SIZE ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  udd_ctrl_buffer ; 
 scalar_t__ udd_ctrl_payload_nb_trans ; 
 scalar_t__ udd_ctrl_prev_payload_nb_trans ; 
 int /*<<< orphan*/  udd_ep_control_state ; 
 TYPE_2__ udd_g_ctrlreq ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_endpoint_setup_buffer_job (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_endpoint_write_buffer_job (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void udd_ctrl_in_sent(void) {
    static bool b_shortpacket = false;
    uint16_t    nb_remain;

    nb_remain = udd_g_ctrlreq.payload_size - udd_ctrl_payload_nb_trans;

    if (0 == nb_remain) {
        /* All content of current buffer payload are sent Update number of total data sending by previous payload buffer */
        udd_ctrl_prev_payload_nb_trans += udd_ctrl_payload_nb_trans;
        if ((udd_g_ctrlreq.req.wLength == udd_ctrl_prev_payload_nb_trans) || b_shortpacket) {
            /* All data requested are transferred or a short packet has been sent, then it is the end of data phase.
             * Generate an OUT ZLP for handshake phase */
            udd_ep_control_state = UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP;
            usb_device_endpoint_setup_buffer_job(&usb_device, udd_ctrl_buffer);
            return;
        }
        /* Need of new buffer because the data phase is not complete */
        if ((!udd_g_ctrlreq.over_under_run) || (!udd_g_ctrlreq.over_under_run())) {
            /* Under run then send zlp on IN
             * Here nb_remain=0, this allows to send a IN ZLP */
        } else {
            /* A new payload buffer is given */
            udd_ctrl_payload_nb_trans = 0;
            nb_remain                 = udd_g_ctrlreq.payload_size;
        }
    }

    /* Continue transfer and send next data */
    if (nb_remain >= USB_DEVICE_EP_CTRL_SIZE) {
        nb_remain     = USB_DEVICE_EP_CTRL_SIZE;
        b_shortpacket = false;
    } else {
        b_shortpacket = true;
    }

    /* Link payload buffer directly on USB hardware */
    usb_device_endpoint_write_buffer_job(&usb_device, 0, udd_g_ctrlreq.payload + udd_ctrl_payload_nb_trans, nb_remain);

    udd_ctrl_payload_nb_trans += nb_remain;
}