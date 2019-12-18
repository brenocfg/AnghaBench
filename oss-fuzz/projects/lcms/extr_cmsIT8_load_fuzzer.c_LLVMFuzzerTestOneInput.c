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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ cmsHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  cmsIT8Free (scalar_t__) ; 
 scalar_t__ cmsIT8LoadFromMem (int /*<<< orphan*/ ,void*,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  cmsHANDLE handle = cmsIT8LoadFromMem(0, (void *)data, size);
  if (handle)
    cmsIT8Free(handle);

  return 0;
}