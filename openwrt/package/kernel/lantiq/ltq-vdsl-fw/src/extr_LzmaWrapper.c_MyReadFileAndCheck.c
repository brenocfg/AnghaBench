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
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 
 int rpos ; 

__attribute__((used)) static int MyReadFileAndCheck(unsigned char *src, void *dest, size_t size)
{
  if (size == 0)
    return 0;
  memcpy(dest, src + rpos, size);
  rpos += size;
  return 1;
}