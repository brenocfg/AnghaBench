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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compress2 (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  data ; 
 size_t dataLen ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  uncompress (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void check_compress_level(uint8_t *compr, size_t comprLen,
                                 uint8_t *uncompr, size_t uncomprLen,
                                 int level) {
  compress2(compr, &comprLen, data, dataLen, level);
  uncompress(uncompr, &uncomprLen, compr, comprLen);

  /* Make sure compress + uncompress gives back the input data. */
  assert(dataLen == uncomprLen);
  assert(0 == memcmp(data, uncompr, dataLen));
}