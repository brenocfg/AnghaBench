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
struct TYPE_6__ {unsigned char* next_in; int avail_in; unsigned char* next_out; unsigned int avail_out; void* opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  TYPE_1__ z_stream ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERR (int,char*) ; 
 int Z_DATA_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_1__*) ; 
 int inflateInit (TYPE_1__*) ; 
 int inflateSync (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zalloc ; 
 int /*<<< orphan*/  zfree ; 

void test_sync(unsigned char *compr, size_t comprLen, unsigned char *uncompr,
               size_t uncomprLen) {
  int err;
  z_stream d_stream; /* decompression stream */

  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (void *)0;

  d_stream.next_in = compr;
  d_stream.avail_in = 2; /* just read the zlib header */

  err = inflateInit(&d_stream);
  CHECK_ERR(err, "inflateInit");

  d_stream.next_out = uncompr;
  d_stream.avail_out = (unsigned int)uncomprLen;

  err = inflate(&d_stream, Z_NO_FLUSH);
  CHECK_ERR(err, "inflate");

  d_stream.avail_in = (unsigned int)comprLen - 2; /* read all compressed data */
  err = inflateSync(&d_stream); /* but skip the damaged part */
  CHECK_ERR(err, "inflateSync");

  err = inflate(&d_stream, Z_FINISH);
  if (err != Z_DATA_ERROR) {
    fprintf(stderr, "inflate should report DATA_ERROR\n");
    /* Because of incorrect adler32 */
    exit(1);
  }
  err = inflateEnd(&d_stream);
  CHECK_ERR(err, "inflateEnd");
}