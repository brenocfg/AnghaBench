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
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_A ; 
 int /*<<< orphan*/  TYPE_ANY ; 
 int /*<<< orphan*/  TYPE_CNAME ; 
 int /*<<< orphan*/  TYPE_MX ; 
 int /*<<< orphan*/  TYPE_NS ; 
 int /*<<< orphan*/  TYPE_PTR ; 
 int /*<<< orphan*/  TYPE_SOA ; 
 int /*<<< orphan*/  TYPE_WKS ; 
 int /*<<< orphan*/  TypeA ; 
 int /*<<< orphan*/  TypeAny ; 
 int /*<<< orphan*/  TypeCNAME ; 
 int /*<<< orphan*/  TypeMX ; 
 int /*<<< orphan*/  TypeNS ; 
 int /*<<< orphan*/  TypePTR ; 
 int /*<<< orphan*/  TypeSOA ; 
 int /*<<< orphan*/  TypeSRV ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

USHORT TypeNametoTypeID( PCHAR TypeName )
{
    if( !strncmp( TypeName, TypeA, strlen( TypeA ) ) ) return TYPE_A;
    if( !strncmp( TypeName, TypeNS, strlen( TypeNS ) ) ) return TYPE_NS;
    if( !strncmp( TypeName, TypeCNAME, strlen( TypeCNAME ) ) ) return TYPE_CNAME;
    if( !strncmp( TypeName, TypeSOA, strlen( TypeSOA ) ) ) return TYPE_SOA;
    if( !strncmp( TypeName, TypeSRV, strlen( TypeSRV ) ) ) return TYPE_WKS;
    if( !strncmp( TypeName, TypePTR, strlen( TypePTR ) ) ) return TYPE_PTR;
    if( !strncmp( TypeName, TypeMX, strlen( TypeMX ) ) ) return TYPE_MX;
    if( !strncmp( TypeName, TypeAny, strlen( TypeAny ) ) ) return TYPE_ANY;

    return 0;
}