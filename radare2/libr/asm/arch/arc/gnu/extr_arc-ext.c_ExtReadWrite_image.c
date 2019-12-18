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
typedef  enum ExtReadWrite { ____Placeholder_ExtReadWrite } ExtReadWrite ;

/* Variables and functions */
#define  REG_INVALID 131 
#define  REG_READ 130 
#define  REG_READWRITE 129 
#define  REG_WRITE 128 

__attribute__((used)) static const char* ExtReadWrite_image(enum ExtReadWrite val)
{
    switch (val)
    {
        case REG_INVALID  : return "INVALID";
        case REG_READ     : return "RO";
        case REG_WRITE    : return "WO";
        case REG_READWRITE: return "R/W";
        default           : return "???";
    }
}