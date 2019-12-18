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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int eventflags_t ;
struct TYPE_3__ {int /*<<< orphan*/  iqueue; } ;
typedef  TYPE_1__ SerialDriver ;

/* Variables and functions */
 int SD_BREAK_DETECTED ; 
 int SD_FRAMING_ERROR ; 
 int SD_NOISE_ERROR ; 
 int SD_OVERRUN_ERROR ; 
 int SD_PARITY_ERROR ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  qSpaceI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_error(char* str, eventflags_t flags, SerialDriver* driver) {
#ifdef DEBUG_LINK_ERRORS
    if (flags & SD_PARITY_ERROR) {
        print(str);
        print(" Parity error\n");
    }
    if (flags & SD_FRAMING_ERROR) {
        print(str);
        print(" Framing error\n");
    }
    if (flags & SD_OVERRUN_ERROR) {
        print(str);
        uint32_t size = qSpaceI(&(driver->iqueue));
        xprintf(" Overrun error, queue size %d\n", size);
    }
    if (flags & SD_NOISE_ERROR) {
        print(str);
        print(" Noise error\n");
    }
    if (flags & SD_BREAK_DETECTED) {
        print(str);
        print(" Break detected\n");
    }
#else
    (void)str;
    (void)flags;
    (void)driver;
#endif
}