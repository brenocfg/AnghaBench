#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int ep_size; int nb_trans; int buf_size; int b_shortpacket; int busy; int /*<<< orphan*/  (* call_trans ) (int /*<<< orphan*/ ,size_t,int) ;int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ udd_ep_job_t ;
typedef  int udd_ep_id_t ;
struct usb_endpoint_callback_parameter {int endpoint_address; int sent_bytes; } ;

/* Variables and functions */
 int UDD_ENDPOINT_MAX_TRANS ; 
 int /*<<< orphan*/  UDD_EP_TRANSFER_OK ; 
 int USB_EP_ADDR_MASK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t,int) ; 
 TYPE_1__* udd_ep_get_job (int) ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_endpoint_write_buffer_job (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void udd_ep_trans_in_next(void *pointer) {
    struct usb_endpoint_callback_parameter *ep_callback_para = (struct usb_endpoint_callback_parameter *)pointer;
    udd_ep_id_t                             ep               = ep_callback_para->endpoint_address;
    uint16_t                                ep_size, nb_trans;
    uint16_t                                next_trans;
    udd_ep_id_t                             ep_num;
    udd_ep_job_t *                          ptr_job;

    ptr_job = udd_ep_get_job(ep);
    ep_num  = ep & USB_EP_ADDR_MASK;

    ep_size = ptr_job->ep_size;
    /* Update number of data transferred */
    nb_trans = ep_callback_para->sent_bytes;
    ptr_job->nb_trans += nb_trans;

    /* Need to send other data */
    if (ptr_job->nb_trans != ptr_job->buf_size) {
        next_trans = ptr_job->buf_size - ptr_job->nb_trans;
        if (UDD_ENDPOINT_MAX_TRANS < next_trans) {
            /* The USB hardware support a maximum
             * transfer size of UDD_ENDPOINT_MAX_TRANS Bytes */
            next_trans = UDD_ENDPOINT_MAX_TRANS - (UDD_ENDPOINT_MAX_TRANS % ep_size);
        }
        /* Need ZLP, if requested and last packet is not a short packet */
        ptr_job->b_shortpacket = ptr_job->b_shortpacket && (0 == (next_trans % ep_size));
        usb_device_endpoint_write_buffer_job(&usb_device, ep_num, &ptr_job->buf[ptr_job->nb_trans], next_trans);
        return;
    }

    /* Need to send a ZLP after all data transfer */
    if (ptr_job->b_shortpacket) {
        ptr_job->b_shortpacket = false;
        /* Start new transfer */
        usb_device_endpoint_write_buffer_job(&usb_device, ep_num, &ptr_job->buf[ptr_job->nb_trans], 0);
        return;
    }

    /* Job complete then call callback */
    ptr_job->busy = false;
    if (NULL != ptr_job->call_trans) {
        ptr_job->call_trans(UDD_EP_TRANSFER_OK, ptr_job->nb_trans, ep);
    }
}