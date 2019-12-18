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
#define  GPIOA0_BASE 131 
#define  GPIOA1_BASE 130 
#define  GPIOA2_BASE 129 
#define  GPIOA3_BASE 128 
 unsigned int INT_GPIOA0 ; 
 unsigned int INT_GPIOA1 ; 
 unsigned int INT_GPIOA2 ; 
 unsigned int INT_GPIOA3 ; 

__attribute__((used)) static long
GPIOGetIntNumber(unsigned long ulPort)
{
    unsigned int ulInt;

    //
    // Determine the GPIO interrupt number for the given module.
    //
    switch(ulPort)
    {
        case GPIOA0_BASE:
        {
            ulInt = INT_GPIOA0;
            break;
        }

        case GPIOA1_BASE:
        {
            ulInt = INT_GPIOA1;
            break;
        }

        case GPIOA2_BASE:
        {
            ulInt = INT_GPIOA2;
            break;
        }

        case GPIOA3_BASE:
        {
            ulInt = INT_GPIOA3;
            break;
        }

        default:
        {
            return(-1);
        }
    }

    //
    // Return GPIO interrupt number.
    //
    return(ulInt);
}