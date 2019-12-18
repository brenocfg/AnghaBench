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
 int GET_FIELD (unsigned int,int,int) ; 
 int sign_extend (int,int) ; 

__attribute__((used)) static int
extract_12 (unsigned word)
{
  return sign_extend (GET_FIELD (word, 19, 28)
		      | GET_FIELD (word, 29, 29) << 10
		      | (word & 0x1) << 11, 12) << 2;
}