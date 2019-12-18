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
 int /*<<< orphan*/  data ; 
 int dataLen ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uncompress (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  write_zlib_header (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_decompress(uint8_t *compr, size_t comprLen) {
  /* We need to write a valid zlib header of size two bytes. Copy the input data
     in a larger buffer. Do not modify the input data to avoid libFuzzer error:
     fuzz target overwrites its const input. */
  size_t copyLen = dataLen + 2;
  uint8_t *copy = (uint8_t *)malloc(copyLen);
  memcpy(copy + 2, data, dataLen);
  write_zlib_header(copy);

  uncompress(compr, &comprLen, copy, copyLen);
  free(copy);
}