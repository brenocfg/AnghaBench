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
typedef  void* uint8_t ;
struct TYPE_3__ {void* wLength; void* wIndex; void* wValue; void* bRequest; void* bmRequest; } ;
typedef  TYPE_1__ USBD_SetupReqTypedef ;

/* Variables and functions */
 void* SWAPBYTE (void**) ; 

void USBD_ParseSetupRequest(USBD_SetupReqTypedef *req, uint8_t *pdata)
{
  req->bmRequest     = *(uint8_t *)  (pdata);
  req->bRequest      = *(uint8_t *)  (pdata +  1);
  req->wValue        = SWAPBYTE      (pdata +  2);
  req->wIndex        = SWAPBYTE      (pdata +  4);
  req->wLength       = SWAPBYTE      (pdata +  6);

}