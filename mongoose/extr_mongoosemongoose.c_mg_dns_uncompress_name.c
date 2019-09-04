#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct mg_str {scalar_t__ p; } ;
struct TYPE_2__ {int len; scalar_t__ p; } ;
struct mg_dns_message {TYPE_1__ pkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,int) ; 

size_t mg_dns_uncompress_name(struct mg_dns_message *msg, struct mg_str *name,
                              char *dst, int dst_len) {
  int chunk_len, num_ptrs = 0;
  char *old_dst = dst;
  const unsigned char *data = (unsigned char *) name->p;
  const unsigned char *end = (unsigned char *) msg->pkt.p + msg->pkt.len;

  if (data >= end) {
    return 0;
  }

  while ((chunk_len = *data++)) {
    int leeway = dst_len - (dst - old_dst);
    if (data >= end) {
      return 0;
    }

    if ((chunk_len & 0xc0) == 0xc0) {
      uint16_t off = (data[-1] & (~0xc0)) << 8 | data[0];
      if (off >= msg->pkt.len) {
        return 0;
      }
      /* Basic circular loop avoidance: allow up to 16 pointer hops. */
      if (++num_ptrs > 15) {
        return 0;
      }
      data = (unsigned char *) msg->pkt.p + off;
      continue;
    }
    if (chunk_len > 63) {
      return 0;
    }
    if (chunk_len > leeway) {
      chunk_len = leeway;
    }

    if (data + chunk_len >= end) {
      return 0;
    }

    memcpy(dst, data, chunk_len);
    data += chunk_len;
    dst += chunk_len;
    leeway -= chunk_len;
    if (leeway == 0) {
      return dst - old_dst;
    }
    *dst++ = '.';
  }

  if (dst != old_dst) {
    *--dst = 0;
  }
  return dst - old_dst;
}