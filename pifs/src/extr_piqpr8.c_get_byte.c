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
 double fabs (double) ; 
 double floor (double) ; 
 double series (int,int) ; 

unsigned char get_byte(int id)
{
  double s1 = series (1, id);
  double s2 = series (4, id);
  double s3 = series (5, id);
  double s4 = series (6, id);
  double pid = 4. * s1 - 2. * s2 - s3 - s4;
  pid = pid - (int) pid + 1.;

  double y = fabs(pid);
  y = 16. * (y - floor (y));
  unsigned char first = y;
  y = 16. * (y - floor (y));
  unsigned char second = y;
  return (first << 4) | second;
}