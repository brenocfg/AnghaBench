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
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  r1 ;

/* Variables and functions */
 scalar_t__ memcmp (double*,double*,int) ; 

__attribute__((used)) static int sqlite3RealSameAsInt(double r1, sqlite3_int64 i){
  double r2 = (double)i;
  return memcmp(&r1, &r2, sizeof(r1))==0;
}