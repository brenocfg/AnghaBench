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
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int check_segment (unsigned char const*,size_t) ; 
 size_t coap_buildOptionHeader (int /*<<< orphan*/ ,int,unsigned char*,size_t) ; 
 int /*<<< orphan*/  decode_segment (unsigned char const*,size_t,unsigned char*) ; 

int make_decoded_option(const unsigned char *s, size_t length,
		    unsigned char *buf, size_t buflen) {
  int res;
  size_t written;

  if (!buflen) {
    NODE_DBG("make_decoded_option(): buflen is 0!\n");
    return -1;
  }

  res = check_segment(s, length);
  if (res < 0)
    return -1;

  /* write option header using delta 0 and length res */
  // written = coap_opt_setheader(buf, buflen, 0, res);
  written = coap_buildOptionHeader(0, res, buf, buflen);

  assert(written <= buflen);

  if (!written)			/* encoding error */
    return -1;

  buf += written;		/* advance past option type/length */
  buflen -= written;

  if (buflen < (size_t)res) {
    NODE_DBG("buffer too small for option\n");
    return -1;
  }

  decode_segment(s, length, buf);

  return written + res;
}