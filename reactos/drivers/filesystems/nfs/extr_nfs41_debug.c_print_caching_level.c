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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  DbgP (char*,int /*<<< orphan*/ ) ; 

void print_caching_level(int on, ULONG flag, PUNICODE_STRING name)
{
    if (!on) return;
    switch(flag) {
        case 0: 
            DbgP("enable_caching: DISABLE_CACHING %wZ\n", name);
            break;
        case 1:
            DbgP("enable_caching: ENABLE_READ_CACHING %wZ\n", name);
            break;
        case 2:
            DbgP("enable_caching: ENABLE_WRITE_CACHING %wZ\n", name);
            break;
        case 3:
            DbgP("enable_caching: ENABLE_READWRITE_CACHING %wZ\n", name);
            break;   
    }
}