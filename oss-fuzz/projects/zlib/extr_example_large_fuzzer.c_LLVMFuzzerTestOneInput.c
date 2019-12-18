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

/* Variables and functions */
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  const* data ; 
 size_t dataLen ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_large_deflate (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  test_large_inflate (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *d, size_t size) {
  size_t comprLen = 100 + 3 * size;
  size_t uncomprLen = comprLen;
  uint8_t *compr, *uncompr;

  /* Discard inputs larger than 512Kb. */
  static size_t kMaxSize = 512 * 1024;

  if (size < 1 || size > kMaxSize)
    return 0;

  data = d;
  dataLen = size;
  compr = (uint8_t *)calloc(1, comprLen);
  uncompr = (uint8_t *)calloc(1, uncomprLen);

  test_large_deflate(compr, comprLen, uncompr, uncomprLen);
  test_large_inflate(compr, comprLen, uncompr, uncomprLen);

  free(compr);
  free(uncompr);

  /* This function must return 0. */
  return 0;
}