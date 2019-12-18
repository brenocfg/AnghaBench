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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  STATE_CLOSING 135 
#define  STATE_ESTABLISHED_RECV 134 
#define  STATE_ESTABLISHED_SEND 133 
#define  STATE_FIN_WAIT1 132 
#define  STATE_FIN_WAIT2 131 
#define  STATE_LAST_ACK 130 
#define  STATE_SYN_SENT 129 
#define  STATE_TIME_WAIT 128 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,int) ; 

__attribute__((used)) static const char *
state_to_string(int state)
{
    static char buf[64];
    switch (state) {
            //STATE_SYN_RECEIVED,
            //STATE_CLOSE_WATI,
        case STATE_LAST_ACK:        return "LAST-ACK";
        case STATE_FIN_WAIT1:       return "FIN-WAIT-1";
        case STATE_FIN_WAIT2:       return "FIN-WAIT-2";
        case STATE_CLOSING:         return "CLOSING";
        case STATE_TIME_WAIT:       return "TIME-WAIT";
        case STATE_SYN_SENT:        return "SYN_SENT";
        case STATE_ESTABLISHED_SEND:return "ESTABLISHED_SEND";
        case STATE_ESTABLISHED_RECV:return "ESTABLISHED_RECV";
            
        default:
            sprintf_s(buf, sizeof(buf), "%d", state);
            return buf;
    }
}