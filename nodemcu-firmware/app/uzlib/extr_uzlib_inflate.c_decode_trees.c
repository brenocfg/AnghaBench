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
typedef  int uint ;
typedef  int uchar ;
typedef  int /*<<< orphan*/  UZLIB_TREE ;
struct TYPE_5__ {size_t* clcidx; } ;
typedef  TYPE_1__ UZLIB_DATA ;

/* Variables and functions */
 int UZLIB_DATA_ERROR ; 
 int UZLIB_OK ; 
 int /*<<< orphan*/  build_tree (int /*<<< orphan*/ *,int*,int) ; 
 int decode_symbol (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int read_bits (TYPE_1__*,int,int) ; 

__attribute__((used)) static int decode_trees (UZLIB_DATA *d, UZLIB_TREE *lt, UZLIB_TREE *dt) {
  uchar lengths[288+32];
  uint hlit, hdist, hclen, hlimit;
  uint i, num, length;

  /* get 5 bits HLIT (257-286) */
  hlit = read_bits(d, 5, 257);

  /* get 5 bits HDIST (1-32) */
  hdist = read_bits(d, 5, 1);

  /* get 4 bits HCLEN (4-19) */
  hclen = read_bits(d, 4, 4);

  for (i = 0; i < 19; ++i) lengths[i] = 0;

  /* read code lengths for code length alphabet */
  for (i = 0; i < hclen; ++i) {
    /* get 3 bits code length (0-7) */
    uint clen = read_bits(d, 3, 0);
    lengths[d->clcidx[i]] = clen;
  }

  /* build code length tree, temporarily use length tree */
  build_tree(lt, lengths, 19);

  /* decode code lengths for the dynamic trees */
  hlimit = hlit + hdist;
  for (num = 0; num < hlimit; ) {
    int sym = decode_symbol(d, lt);
    uchar fill_value = 0;
    int lbits, lbase = 3;

    /* error decoding */
    if (sym < 0)
      return sym;

    switch (sym) {
    case 16:
      /* copy previous code length 3-6 times (read 2 bits) */
      fill_value = lengths[num - 1];
      lbits = 2;
      break;
    case 17:
      /* repeat code length 0 for 3-10 times (read 3 bits) */
      lbits = 3;
      break;
    case 18:
      /* repeat code length 0 for 11-138 times (read 7 bits) */
      lbits = 7;
      lbase = 11;
      break;
    default:
      /* values 0-15 represent the actual code lengths */
      lengths[num++] = sym;
      /* continue the for loop */
      continue;
    }

    /* special code length 16-18 are handled here */
    length = read_bits(d, lbits, lbase);
    if (num + length > hlimit)
      return UZLIB_DATA_ERROR;

    for (; length; --length)
      lengths[num++] = fill_value;
  }

  /* build dynamic trees */
  build_tree(lt, lengths, hlit);
  build_tree(dt, lengths + hlit, hdist);

  return UZLIB_OK;
}