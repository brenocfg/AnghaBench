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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  outmode ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_compress (char*,char*) ; 
 int /*<<< orphan*/  file_uncompress (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 size_t fwrite (int const*,int,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int const*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t dataLen) {
  char *inFileName = "/tmp/minigzip_fuzzer.out";
  char *outFileName = "/tmp/minigzip_fuzzer.out.gz";
  char outmode[20];
  FILE *in;
  char buf[BUFLEN];
  uint32_t offset = 0;

  /* Discard inputs larger than 1Mb. */
  static size_t kMaxSize = 1024 * 1024;
  if (dataLen < 1 || dataLen > kMaxSize)
    return 0;

  in = fopen(inFileName, "w");
  if (fwrite(data, 1, (unsigned)dataLen, in) != dataLen)
    error("failed fwrite");
  if (fclose(in))
    error("failed fclose");

  memset(outmode, 0, sizeof(outmode));
  snprintf(outmode, sizeof(outmode), "%s", "wb");

  /* Compression level: [0..9]. */
  outmode[2] = data[0] % 10;

  switch (data[0] % 4) {
  default:
  case 0:
    outmode[3] = 0;
    break;
  case 1:
    /* compress with Z_FILTERED */
    outmode[3] = 'f';
    break;
  case 2:
    /* compress with Z_HUFFMAN_ONLY */
    outmode[3] = 'h';
    break;
  case 3:
    /* compress with Z_RLE */
    outmode[3] = 'R';
    break;
  }

  file_compress(inFileName, outmode);
  file_uncompress(outFileName);

  /* Check that the uncompressed file matches the input data. */
  in = fopen(inFileName, "rb");
  if (in == NULL) {
    perror(inFileName);
    exit(1);
  }

  memset(buf, 0, sizeof(buf));
  for (;;) {
    int len = (int)fread(buf, 1, sizeof(buf), in);
    if (ferror(in)) {
      perror("fread");
      exit(1);
    }
    if (len == 0)
      break;
    assert(0 == memcmp(data + offset, buf, len));
    offset += len;
  }

  if (fclose(in))
    error("failed fclose");

  /* This function must return 0. */
  return 0;
}