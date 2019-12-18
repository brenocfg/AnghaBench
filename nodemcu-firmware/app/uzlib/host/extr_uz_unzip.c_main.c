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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  uchar ;
typedef  int /*<<< orphan*/  outBlock ;
struct TYPE_5__ {int len; int breakNdx; int /*<<< orphan*/ * fin; struct TYPE_5__** block; int /*<<< orphan*/  crc; int /*<<< orphan*/  fullBlkCB; int /*<<< orphan*/ * fout; } ;

/* Variables and functions */
 int DICTIONARY_WINDOW ; 
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int UZLIB_CHKSUM_ERROR ; 
 int WRITE_BLOCKS ; 
 int WRITE_BLOCKSIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* fopen (char const*,char*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_byte ; 
 TYPE_1__* in ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* out ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  processOutRec ; 
 int /*<<< orphan*/  put_byte ; 
 int /*<<< orphan*/  recall_byte ; 
 void* uz_malloc (int) ; 
 int uzlib_inflate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void**) ; 

int main(int argc, char *argv[]) {
  assert (argc==3);
  const char *inFile = argv[1], *outFile = argv[2];
  int i, n, res;
  uint crc;
  void *cxt_not_used;
  assert(sizeof(unsigned int) == 4);

  /* allocate and zero the in and out Blocks */
  assert((in  = uz_malloc(sizeof(*in))) != NULL);
  assert((out = uz_malloc(sizeof(*out))) != NULL);

  memset(in, 0, sizeof(*in));
  memset(out, 0, sizeof(*out));

  /* open input files and probe end to read the expanded length */
  assert((in->fin = fopen(inFile, "rb")) != NULL);
  fseek(in->fin, -4, SEEK_END);
  assert(fread((uchar*)&(out->len), 1, 4, in->fin) == 4);
  in->len = ftell(in->fin);
  fseek(in->fin, 0, SEEK_SET);

  assert((out->fout = fopen(outFile, "wb")) != NULL);

  printf ("Inflating in=%s out=%s\n", inFile, outFile);

  /* Allocate the out buffers (number depends on the unpacked length) */
  n = (out->len > DICTIONARY_WINDOW) ? WRITE_BLOCKS :
                                      1 + (out->len-1) / WRITE_BLOCKSIZE;
  for(i = WRITE_BLOCKS - n + 1;  i <= WRITE_BLOCKS; i++)
    assert((out->block[i % WRITE_BLOCKS] = uz_malloc(sizeof(outBlock))) != NULL);

  out->breakNdx  = (out->len < WRITE_BLOCKSIZE) ? out->len : WRITE_BLOCKSIZE;
  out->fullBlkCB = processOutRec;
  out->crc       = ~0;

  /* Call inflate to do the business */
  res = uzlib_inflate (get_byte, put_byte, recall_byte, in->len, &crc, &cxt_not_used);

  if (res > 0 && crc != ~out->crc)
    res = UZLIB_CHKSUM_ERROR;

  for (i = 0; i < WRITE_BLOCKS; i++)
    FREE(out->block[i]);

  fclose(in->fin);
  FREE(in);
  FREE(out);

  if (res < 0)
    printf("Error during decompression: %d\n", res);

  return (res != 0) ? 1: 0;
}