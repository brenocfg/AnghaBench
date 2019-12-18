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
#define  P_ACK_V1 137 
#define  P_CONTROL_HARD_RESET_CLIENT_V1 136 
#define  P_CONTROL_HARD_RESET_CLIENT_V2 135 
#define  P_CONTROL_HARD_RESET_CLIENT_V3 134 
#define  P_CONTROL_HARD_RESET_SERVER_V1 133 
#define  P_CONTROL_HARD_RESET_SERVER_V2 132 
#define  P_CONTROL_SOFT_RESET_V1 131 
#define  P_CONTROL_V1 130 
#define  P_DATA_V1 129 
#define  P_DATA_V2 128 

__attribute__((used)) static const char *
packet_opcode_name(int op)
{
    switch (op)
    {
        case P_CONTROL_HARD_RESET_CLIENT_V1:
            return "P_CONTROL_HARD_RESET_CLIENT_V1";

        case P_CONTROL_HARD_RESET_SERVER_V1:
            return "P_CONTROL_HARD_RESET_SERVER_V1";

        case P_CONTROL_HARD_RESET_CLIENT_V2:
            return "P_CONTROL_HARD_RESET_CLIENT_V2";

        case P_CONTROL_HARD_RESET_SERVER_V2:
            return "P_CONTROL_HARD_RESET_SERVER_V2";

        case P_CONTROL_HARD_RESET_CLIENT_V3:
            return "P_CONTROL_HARD_RESET_CLIENT_V3";

        case P_CONTROL_SOFT_RESET_V1:
            return "P_CONTROL_SOFT_RESET_V1";

        case P_CONTROL_V1:
            return "P_CONTROL_V1";

        case P_ACK_V1:
            return "P_ACK_V1";

        case P_DATA_V1:
            return "P_DATA_V1";

        case P_DATA_V2:
            return "P_DATA_V2";

        default:
            return "P_???";
    }
}