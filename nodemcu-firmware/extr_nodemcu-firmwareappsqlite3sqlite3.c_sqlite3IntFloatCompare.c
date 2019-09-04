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
typedef  scalar_t__ i64 ;
typedef  double LONGDOUBLE_TYPE ;

/* Variables and functions */
 scalar_t__ SMALLEST_INT64 ; 

__attribute__((used)) static int sqlite3IntFloatCompare(i64 i, double r){
  if( sizeof(LONGDOUBLE_TYPE)>8 ){
    LONGDOUBLE_TYPE x = (LONGDOUBLE_TYPE)i;
    if( x<r ) return -1;
    if( x>r ) return +1;
    return 0;
  }else{
    i64 y;
    double s;
    if( r<-9223372036854775808.0 ) return +1;
    if( r>9223372036854775807.0 ) return -1;
    y = (i64)r;
    if( i<y ) return -1;
    if( i>y ){
      if( y==SMALLEST_INT64 && r>0.0 ) return -1;
      return +1;
    }
    s = (double)i;
    if( s<r ) return -1;
    if( s>r ) return +1;
    return 0;
  }
}