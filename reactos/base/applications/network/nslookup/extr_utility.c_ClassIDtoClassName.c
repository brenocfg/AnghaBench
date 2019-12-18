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
#define  CLASS_ANY 129 
#define  CLASS_IN 128 
 char* ClassAny ; 
 char* ClassIN ; 

PCHAR ClassIDtoClassName( USHORT ClassID )
{
    switch( ClassID )
    {
    case CLASS_IN:
        return ClassIN;

    case CLASS_ANY:
        return ClassAny;
        
    default:
        return "Unknown";
    }
}