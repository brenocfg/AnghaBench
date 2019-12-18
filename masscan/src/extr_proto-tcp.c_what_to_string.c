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
typedef  enum TCP_What { ____Placeholder_TCP_What } TCP_What ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  TCP_WHAT_ACK 133 
#define  TCP_WHAT_DATA 132 
#define  TCP_WHAT_FIN 131 
#define  TCP_WHAT_RST 130 
#define  TCP_WHAT_SYNACK 129 
#define  TCP_WHAT_TIMEOUT 128 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,int) ; 

__attribute__((used)) static const char *
what_to_string(enum TCP_What state)
{
    static char buf[64];
    switch (state) {
        case TCP_WHAT_TIMEOUT: return "TIMEOUT";
        case TCP_WHAT_SYNACK: return "SYNACK";
        case TCP_WHAT_RST: return "RST";
        case TCP_WHAT_FIN: return "FIN";
        case TCP_WHAT_ACK: return "ACK";
        case TCP_WHAT_DATA: return "DATA";
        default:
            sprintf_s(buf, sizeof(buf), "%d", state);
            return buf;
    }
}