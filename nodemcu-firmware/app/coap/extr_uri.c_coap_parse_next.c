#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ n; scalar_t__ segment_length; unsigned char* pos; unsigned char separator; int /*<<< orphan*/  dlen; int /*<<< orphan*/  delim; } ;
typedef  TYPE_1__ coap_parse_iterator_t ;

/* Variables and functions */
 scalar_t__ strnchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

unsigned char * coap_parse_next(coap_parse_iterator_t *pi) {
  unsigned char *p;

  if (!pi)
    return NULL;

  /* proceed to the next segment */
  pi->n -= pi->segment_length;
  pi->pos += pi->segment_length;
  pi->segment_length = 0;

  /* last segment? */
  if (!pi->n || strnchr(pi->delim, pi->dlen, *pi->pos)) {
    pi->pos = NULL;
    return NULL;
  }

  /* skip following separator (the first segment might not have one) */
  if (*pi->pos == pi->separator) {
    ++pi->pos;
    --pi->n;
  }

  p = pi->pos;

  while (pi->segment_length < pi->n && *p != pi->separator &&
	 !strnchr(pi->delim, pi->dlen, *p)) {
    ++p;
    ++pi->segment_length;
  }

  if (!pi->n) {
    pi->pos = NULL;
    pi->segment_length = 0;
  }

  return pi->pos;
}