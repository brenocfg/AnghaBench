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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_hexdump_n (char const*,int,char*,int,int) ; 

void mg_hexdumpf(FILE *fp, const void *buf, int len) {
  char tmp[80];
  int offset = 0, n;
  while (len > 0) {
    n = (len < 16 ? len : 16);
    mg_hexdump_n(((const char *) buf) + offset, n, tmp, sizeof(tmp), offset);
    fputs(tmp, fp);
    offset += n;
    len -= n;
  }
}