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
#define  RCODE_FAILURE 133 
#define  RCODE_FORMERR 132 
#define  RCODE_NOERROR 131 
#define  RCODE_NOTIMP 130 
#define  RCODE_NXDOMAIN 129 
#define  RCODE_REFUSED 128 
 int /*<<< orphan*/  RCodeFAILURE ; 
 int /*<<< orphan*/  RCodeFORMERR ; 
 int /*<<< orphan*/  RCodeNOERROR ; 
 int /*<<< orphan*/  RCodeNOTIMP ; 
 int /*<<< orphan*/  RCodeNXDOMAIN ; 
 int /*<<< orphan*/  RCodeREFUSED ; 
 int /*<<< orphan*/  RCodeReserved ; 

PCHAR RCodeIDtoRCodeName( UCHAR RCode )
{
    switch( RCode & 0x0F )
    {
    case RCODE_NOERROR:
        return RCodeNOERROR;

    case RCODE_FORMERR:
        return RCodeFORMERR;

    case RCODE_FAILURE:
        return RCodeFAILURE;

    case RCODE_NXDOMAIN:
        return RCodeNXDOMAIN;

    case RCODE_NOTIMP:
        return RCodeNOTIMP;

    case RCODE_REFUSED:
        return RCodeREFUSED;

    default:
        return RCodeReserved;
    }
}