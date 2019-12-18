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
struct TYPE_5__ {unsigned char* next_in; int avail_in; unsigned char* next_out; size_t total_out; size_t total_in; int avail_out; void* opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  TYPE_1__ z_stream ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERR (int,char*) ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  dataLen ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_1__*) ; 
 int inflateInit (TYPE_1__*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zalloc ; 
 int /*<<< orphan*/  zfree ; 

void test_inflate(unsigned char *compr, size_t comprLen, unsigned char *uncompr,
                  size_t uncomprLen) {
  int err;
  z_stream d_stream; /* decompression stream */

  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (void *)0;

  d_stream.next_in = compr;
  d_stream.avail_in = 0;
  d_stream.next_out = uncompr;

  err = inflateInit(&d_stream);
  CHECK_ERR(err, "inflateInit");

  while (d_stream.total_out < uncomprLen && d_stream.total_in < comprLen) {
    d_stream.avail_in = d_stream.avail_out = 1; /* force small buffers */
    err = inflate(&d_stream, Z_NO_FLUSH);
    if (err == Z_STREAM_END)
      break;
    CHECK_ERR(err, "inflate");
  }

  err = inflateEnd(&d_stream);
  CHECK_ERR(err, "inflateEnd");

  if (memcmp(uncompr, data, dataLen)) {
    fprintf(stderr, "bad inflate\n");
    exit(1);
  }
}