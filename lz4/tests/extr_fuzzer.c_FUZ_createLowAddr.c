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
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,void* const) ; 
 int MAP_ANONYMOUS ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 void* mmap (void*,size_t,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* FUZ_createLowAddr(size_t size)
{
    void* const lowBuff = mmap((void*)(0x1000), size,
                    PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
                    -1, 0);
    DISPLAYLEVEL(2, "generating low buffer at address %p \n", lowBuff);
    return lowBuff;
}