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

__attribute__((used)) static int
extract_3 (unsigned word)
{
  return GET_FIELD (word, 18, 18) << 2 | GET_FIELD (word, 16, 17);
}