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
 int compressBound (size_t) ; 
 int /*<<< orphan*/  const* data ; 
 size_t dataLen ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_flush (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  test_sync (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *d, size_t size) {
  size_t comprLen = 100 + 2 * compressBound(size);
  size_t uncomprLen = size;
  uint8_t *compr, *uncompr;

  /* Discard inputs larger than 1Mb. */
  static size_t kMaxSize = 1024 * 1024;

  // This test requires at least 3 bytes of input data.
  if (size <= 3 || size > kMaxSize)
    return 0;

  data = d;
  dataLen = size;
  compr = (uint8_t *)calloc(1, comprLen);
  uncompr = (uint8_t *)calloc(1, uncomprLen);

  test_flush(compr, &comprLen);
  test_sync(compr, comprLen, uncompr, uncomprLen);

  free(compr);
  free(uncompr);

  /* This function must return 0. */
  return 0;
}