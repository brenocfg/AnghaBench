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
 int lsapi_schedule_notify () ; 
 scalar_t__ s_schedule_notify ; 
 int send_req_received_notification (int) ; 

__attribute__((used)) static inline int notify_req_received( int fd )
{
    if ( s_schedule_notify )
        return lsapi_schedule_notify();
    return send_req_received_notification( fd );

}