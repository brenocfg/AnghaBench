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

/* Variables and functions */
 int /*<<< orphan*/  ERREXIT (char*) ; 
#define  M_APP12 144 
#define  M_COM 143 
#define  M_EOI 142 
#define  M_SOF0 141 
#define  M_SOF1 140 
#define  M_SOF10 139 
#define  M_SOF11 138 
#define  M_SOF13 137 
#define  M_SOF14 136 
#define  M_SOF15 135 
#define  M_SOF2 134 
#define  M_SOF3 133 
#define  M_SOF5 132 
#define  M_SOF6 131 
#define  M_SOF7 130 
#define  M_SOF9 129 
 scalar_t__ M_SOI ; 
#define  M_SOS 128 
 scalar_t__ first_marker () ; 
 int next_marker () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  process_COM (int) ; 
 int /*<<< orphan*/  process_SOFn (int) ; 
 int /*<<< orphan*/  skip_variable () ; 

__attribute__((used)) static int
scan_JPEG_header(int verbose, int raw)
{
  int marker;

  /* Expect SOI at start of file */
  if (first_marker() != M_SOI)
    ERREXIT("Expected SOI marker first");

  /* Scan miscellaneous markers until we reach SOS. */
  for (;;) {
    marker = next_marker();
    switch (marker) {
      /* Note that marker codes 0xC4, 0xC8, 0xCC are not, and must not be,
       * treated as SOFn.  C4 in particular is actually DHT.
       */
    case M_SOF0:                /* Baseline */
    case M_SOF1:                /* Extended sequential, Huffman */
    case M_SOF2:                /* Progressive, Huffman */
    case M_SOF3:                /* Lossless, Huffman */
    case M_SOF5:                /* Differential sequential, Huffman */
    case M_SOF6:                /* Differential progressive, Huffman */
    case M_SOF7:                /* Differential lossless, Huffman */
    case M_SOF9:                /* Extended sequential, arithmetic */
    case M_SOF10:               /* Progressive, arithmetic */
    case M_SOF11:               /* Lossless, arithmetic */
    case M_SOF13:               /* Differential sequential, arithmetic */
    case M_SOF14:               /* Differential progressive, arithmetic */
    case M_SOF15:               /* Differential lossless, arithmetic */
      if (verbose)
        process_SOFn(marker);
      else
        skip_variable();
      break;

    case M_SOS:                 /* stop before hitting compressed data */
      return marker;

    case M_EOI:                 /* in case it's a tables-only JPEG stream */
      return marker;

    case M_COM:
      process_COM(raw);
      break;

    case M_APP12:
      /* Some digital camera makers put useful textual information into
       * APP12 markers, so we print those out too when in -verbose mode.
       */
      if (verbose) {
        printf("APP12 contains:\n");
        process_COM(raw);
      } else
        skip_variable();
      break;

    default:                    /* Anything else just gets skipped */
      skip_variable();          /* we assume it has a parameter count... */
      break;
    }
  } /* end loop */
}