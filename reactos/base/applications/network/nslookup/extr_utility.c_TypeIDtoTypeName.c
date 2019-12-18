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
typedef  int USHORT ;
typedef  char* PCHAR ;

/* Variables and functions */
#define  TYPE_A 135 
#define  TYPE_ANY 134 
#define  TYPE_CNAME 133 
#define  TYPE_MX 132 
#define  TYPE_NS 131 
#define  TYPE_PTR 130 
#define  TYPE_SOA 129 
#define  TYPE_WKS 128 
 char* TypeA ; 
 char* TypeAny ; 
 char* TypeCNAME ; 
 char* TypeMX ; 
 char* TypeNS ; 
 char* TypePTR ; 
 char* TypeSOA ; 
 char* TypeSRV ; 

PCHAR TypeIDtoTypeName( USHORT TypeID )
{
    switch( TypeID )
    {
    case TYPE_A:
        return TypeA;

    case TYPE_NS:
        return TypeNS;

    case TYPE_CNAME:
        return TypeCNAME;

    case TYPE_SOA:
        return TypeSOA;

    case TYPE_WKS:
        return TypeSRV;

    case TYPE_PTR:
        return TypePTR;

    case TYPE_MX:
        return TypeMX;

    case TYPE_ANY:
        return TypeAny;

    default:
        return "Unknown";
    }
}