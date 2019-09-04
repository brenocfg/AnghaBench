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
 int /*<<< orphan*/  assert (int) ; 
 int* sqlite3UpperToLower ; 

__attribute__((used)) static unsigned int strHash(const char *z, int nKey){
  int h = 0;
  assert( nKey>=0 );
  while( nKey > 0  ){
    h = (h<<3) ^ h ^ sqlite3UpperToLower[(unsigned char)*z++];
    nKey--;
  }
  return h;
}