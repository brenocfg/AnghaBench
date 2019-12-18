#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Flags; } ;
typedef  TYPE_1__* PIO_STACK_LOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  DbgP (char*,int,char*,char*,char*,char*) ; 
 int SL_CASE_SENSITIVE ; 
 int SL_FORCE_ACCESS_CHECK ; 
 int SL_OPEN_PAGING_FILE ; 
 int SL_OPEN_TARGET_DIRECTORY ; 

void print_irps_flags(int on, PIO_STACK_LOCATION irps)
{
    if (!on) return;
    if (irps->Flags)
        DbgP("IRPSP FLAGS 0x%x %s %s %s %s\n", irps->Flags,
            (irps->Flags & SL_CASE_SENSITIVE)?"CASE_SENSITIVE":"",
            (irps->Flags & SL_OPEN_PAGING_FILE)?"PAGING_FILE":"",
            (irps->Flags & SL_FORCE_ACCESS_CHECK)?"ACCESS_CHECK":"",
            (irps->Flags & SL_OPEN_TARGET_DIRECTORY)?"TARGET_DIR":"");
}