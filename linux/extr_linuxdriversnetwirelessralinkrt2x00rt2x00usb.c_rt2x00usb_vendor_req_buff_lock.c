#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {void* cache; } ;
struct rt2x00_dev {TYPE_1__ csr; int /*<<< orphan*/  csr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ const CSR_CACHE_SIZE ; 
 int ENOMEM ; 
 scalar_t__ const USB_VENDOR_REQUEST_IN ; 
 scalar_t__ const USB_VENDOR_REQUEST_OUT ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__ const) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 int rt2x00usb_vendor_request (struct rt2x00_dev*,scalar_t__ const,scalar_t__ const,scalar_t__ const,int /*<<< orphan*/ ,void*,scalar_t__ const,int const) ; 
 scalar_t__ unlikely (int) ; 

int rt2x00usb_vendor_req_buff_lock(struct rt2x00_dev *rt2x00dev,
				   const u8 request, const u8 requesttype,
				   const u16 offset, void *buffer,
				   const u16 buffer_length, const int timeout)
{
	int status;

	BUG_ON(!mutex_is_locked(&rt2x00dev->csr_mutex));

	/*
	 * Check for Cache availability.
	 */
	if (unlikely(!rt2x00dev->csr.cache || buffer_length > CSR_CACHE_SIZE)) {
		rt2x00_err(rt2x00dev, "CSR cache not available\n");
		return -ENOMEM;
	}

	if (requesttype == USB_VENDOR_REQUEST_OUT)
		memcpy(rt2x00dev->csr.cache, buffer, buffer_length);

	status = rt2x00usb_vendor_request(rt2x00dev, request, requesttype,
					  offset, 0, rt2x00dev->csr.cache,
					  buffer_length, timeout);

	if (!status && requesttype == USB_VENDOR_REQUEST_IN)
		memcpy(buffer, rt2x00dev->csr.cache, buffer_length);

	return status;
}