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

/* Variables and functions */
 int LSAPI_Flush () ; 
 scalar_t__ lsapi_mode ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 

__attribute__((used)) static void sapi_lsapi_flush(void * server_context)
{
    if ( lsapi_mode ) {
        if ( LSAPI_Flush() == -1) {
            php_handle_aborted_connection();
        }
    }
}