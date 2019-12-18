#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned char* next_out; unsigned int avail_out; unsigned char* next_in; unsigned int avail_in; void* opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  TYPE_1__ z_stream ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERR (int,char*) ; 
 int /*<<< orphan*/  Z_BEST_COMPRESSION ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_FILTERED ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  Z_NO_COMPRESSION ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int deflateEnd (TYPE_1__*) ; 
 int deflateInit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateParams (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int diff ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zalloc ; 
 int /*<<< orphan*/  zfree ; 

void test_large_deflate(unsigned char *compr, size_t comprLen,
                        unsigned char *uncompr, size_t uncomprLen) {
  z_stream c_stream; /* compression stream */
  int err;

  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (void *)0;

  err = deflateInit(&c_stream, Z_BEST_COMPRESSION);
  CHECK_ERR(err, "deflateInit");

  c_stream.next_out = compr;
  c_stream.avail_out = (unsigned int)comprLen;

  /* At this point, uncompr is still mostly zeroes, so it should compress
   * very well:
   */
  c_stream.next_in = uncompr;
  c_stream.avail_in = (unsigned int)uncomprLen;
  err = deflate(&c_stream, Z_NO_FLUSH);
  CHECK_ERR(err, "deflate large 1");
  if (c_stream.avail_in != 0) {
    fprintf(stderr, "deflate not greedy\n");
    exit(1);
  }

  /* Feed in already compressed data and switch to no compression: */
  deflateParams(&c_stream, Z_NO_COMPRESSION, Z_DEFAULT_STRATEGY);
  c_stream.next_in = compr;
  diff = (unsigned int)(c_stream.next_out - compr);
  c_stream.avail_in = diff;
  err = deflate(&c_stream, Z_NO_FLUSH);
  CHECK_ERR(err, "deflate large 2");

  /* Switch back to compressing mode: */
  deflateParams(&c_stream, Z_BEST_COMPRESSION, Z_FILTERED);
  c_stream.next_in = uncompr;
  c_stream.avail_in = (unsigned int)uncomprLen;
  err = deflate(&c_stream, Z_NO_FLUSH);
  CHECK_ERR(err, "deflate large 3");

  err = deflate(&c_stream, Z_FINISH);
  if (err != Z_STREAM_END) {
    fprintf(stderr, "deflate large should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  CHECK_ERR(err, "deflateEnd");
}