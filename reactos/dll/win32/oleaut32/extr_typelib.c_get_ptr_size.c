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
typedef  int SYSKIND ;

/* Variables and functions */
#define  SYS_MAC 131 
#define  SYS_WIN16 130 
#define  SYS_WIN32 129 
#define  SYS_WIN64 128 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static int get_ptr_size(SYSKIND syskind)
{
    switch(syskind){
    case SYS_WIN64:
        return 8;
    case SYS_WIN32:
    case SYS_MAC:
    case SYS_WIN16:
        return 4;
    }
    WARN("Unhandled syskind: 0x%x\n", syskind);
    return 4;
}