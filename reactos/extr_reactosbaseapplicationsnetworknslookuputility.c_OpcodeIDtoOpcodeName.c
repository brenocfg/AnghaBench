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
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
#define  OPCODE_IQUERY 130 
#define  OPCODE_QUERY 129 
#define  OPCODE_STATUS 128 
 int /*<<< orphan*/  OpcodeIQuery ; 
 int /*<<< orphan*/  OpcodeQuery ; 
 int /*<<< orphan*/  OpcodeReserved ; 
 int /*<<< orphan*/  OpcodeStatus ; 

PCHAR OpcodeIDtoOpcodeName( UCHAR Opcode )
{
    switch( Opcode & 0x0F )
    {
    case OPCODE_QUERY:
        return OpcodeQuery;

    case OPCODE_IQUERY:
        return OpcodeIQuery;

    case OPCODE_STATUS:
        return OpcodeStatus;

    default:
        return OpcodeReserved;
    }
}