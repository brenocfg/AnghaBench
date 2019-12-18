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
typedef  scalar_t__ HINTERNET ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  InternetCloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  free_session () ; 
 int /*<<< orphan*/  free_tls_list () ; 
 scalar_t__ get_internet_session (int /*<<< orphan*/ *) ; 
 scalar_t__ hCabinet ; 
 int /*<<< orphan*/  unregister_notif_wnd_class () ; 

__attribute__((used)) static void process_detach(void)
{
    HINTERNET internet_session;

    internet_session = get_internet_session(NULL);
    if(internet_session)
        InternetCloseHandle(internet_session);

    if (hCabinet)
        FreeLibrary(hCabinet);

    free_session();
    free_tls_list();
    unregister_notif_wnd_class();
}