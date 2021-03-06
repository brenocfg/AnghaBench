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
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int ion_fd ; 
 int open (char*,int) ; 

__attribute__((used)) static void ion_init() {
  if (ion_fd == -1) {
    ion_fd = open("/dev/ion", O_RDWR | O_NONBLOCK);
  }
}