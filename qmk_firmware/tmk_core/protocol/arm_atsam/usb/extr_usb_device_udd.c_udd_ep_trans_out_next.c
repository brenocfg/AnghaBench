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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ ep_size; int b_use_out_cache_buffer; size_t nb_trans; scalar_t__ buf_size; int busy; int /*<<< orphan*/  (* call_trans ) (int /*<<< orphan*/ ,size_t,int) ;int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ udd_ep_job_t ;
typedef  int udd_ep_id_t ;
struct usb_endpoint_callback_parameter {int endpoint_address; scalar_t__ received_bytes; scalar_t__ out_buffer_size; } ;

/* Variables and functions */
 scalar_t__ UDD_ENDPOINT_MAX_TRANS ; 
 int /*<<< orphan*/  UDD_EP_TRANSFER_OK ; 
 int USB_EP_ADDR_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t,int) ; 
 TYPE_1__* udd_ep_get_job (int) ; 
 int /*<<< orphan*/ ** udd_ep_out_cache_buffer ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_endpoint_read_buffer_job (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void udd_ep_trans_out_next(void *pointer) {
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
    nb_trans = ep_callback_para->received_bytes;

    /* Can be necessary to copy data receive from cache buffer to user buffer */
    if (ptr_job->b_use_out_cache_buffer) {
        memcpy(&ptr_job->buf[ptr_job->nb_trans], udd_ep_out_cache_buffer[ep_num - 1], ptr_job->buf_size % ep_size);
    }

    /* Update number of data transferred */
    ptr_job->nb_trans += nb_trans;
    if (ptr_job->nb_trans > ptr_job->buf_size) {
        ptr_job->nb_trans = ptr_job->buf_size;
    }

    /* If all previous data requested are received and user buffer not full
     * then need to receive other data */
    if ((nb_trans == ep_callback_para->out_buffer_size) && (ptr_job->nb_trans != ptr_job->buf_size)) {
        next_trans = ptr_job->buf_size - ptr_job->nb_trans;
        if (UDD_ENDPOINT_MAX_TRANS < next_trans) {
            /* The USB hardware support a maximum transfer size
             * of UDD_ENDPOINT_MAX_TRANS Bytes */
            next_trans = UDD_ENDPOINT_MAX_TRANS - (UDD_ENDPOINT_MAX_TRANS % ep_size);
        } else {
            next_trans -= next_trans % ep_size;
        }

        if (next_trans < ep_size) {
            /* Use the cache buffer for Bulk or Interrupt size endpoint */
            ptr_job->b_use_out_cache_buffer = true;
            usb_device_endpoint_read_buffer_job(&usb_device, ep_num, udd_ep_out_cache_buffer[ep_num - 1], ep_size);
        } else {
            usb_device_endpoint_read_buffer_job(&usb_device, ep_num, &ptr_job->buf[ptr_job->nb_trans], next_trans);
        }
        return;
    }

    /* Job complete then call callback */
    ptr_job->busy = false;
    if (NULL != ptr_job->call_trans) {
        ptr_job->call_trans(UDD_EP_TRANSFER_OK, ptr_job->nb_trans, ep);
    }
}