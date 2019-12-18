#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* next_in; unsigned int avail_in; unsigned char* next_out; unsigned int avail_out; scalar_t__ total_out; void* opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  TYPE_1__ z_stream ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERR (int,char*) ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_STREAM_END ; 
 scalar_t__ diff ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_1__*) ; 
 int inflateInit (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zalloc ; 
 int /*<<< orphan*/  zfree ; 

void test_large_inflate(unsigned char *compr, size_t comprLen,
                        unsigned char *uncompr, size_t uncomprLen) {
  int err;
  z_stream d_stream; /* decompression stream */

  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (void *)0;

  d_stream.next_in = compr;
  d_stream.avail_in = (unsigned int)comprLen;

  err = inflateInit(&d_stream);
  CHECK_ERR(err, "inflateInit");

  for (;;) {
    d_stream.next_out = uncompr; /* discard the output */
    d_stream.avail_out = (unsigned int)uncomprLen;
    err = inflate(&d_stream, Z_NO_FLUSH);
    if (err == Z_STREAM_END)
      break;
    CHECK_ERR(err, "large inflate");
  }

  err = inflateEnd(&d_stream);
  CHECK_ERR(err, "inflateEnd");

  if (d_stream.total_out != 2 * uncomprLen + diff) {
    fprintf(stderr, "bad large inflate: %zu\n", d_stream.total_out);
    exit(1);
  }
}