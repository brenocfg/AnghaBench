#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ notif_hwnd; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ tls_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 TYPE_1__* TlsGetValue (scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_cs ; 
 scalar_t__ urlmon_tls ; 

__attribute__((used)) static void detach_thread(void)
{
    tls_data_t *data;

    if(urlmon_tls == TLS_OUT_OF_INDEXES)
        return;

    data = TlsGetValue(urlmon_tls);
    if(!data)
        return;

    EnterCriticalSection(&tls_cs);
    list_remove(&data->entry);
    LeaveCriticalSection(&tls_cs);

    if(data->notif_hwnd) {
        WARN("notif_hwnd not destroyed\n");
        DestroyWindow(data->notif_hwnd);
    }

    heap_free(data);
}