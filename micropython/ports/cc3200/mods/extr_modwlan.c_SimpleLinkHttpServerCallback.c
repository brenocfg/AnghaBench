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
struct TYPE_3__ {int Event; } ;
typedef  int /*<<< orphan*/  SlHttpServerResponse_t ;
typedef  TYPE_1__ SlHttpServerEvent_t ;

/* Variables and functions */
#define  SL_NETAPP_HTTPGETTOKENVALUE_EVENT 129 
#define  SL_NETAPP_HTTPPOSTTOKENVALUE_EVENT 128 

void SimpleLinkHttpServerCallback(SlHttpServerEvent_t *pHttpEvent, SlHttpServerResponse_t *pHttpResponse) {
    if (!pHttpEvent) {
        return;
    }

    switch (pHttpEvent->Event) {
    case SL_NETAPP_HTTPGETTOKENVALUE_EVENT:
        break;
    case SL_NETAPP_HTTPPOSTTOKENVALUE_EVENT:
        break;
    default:
        break;
    }
}