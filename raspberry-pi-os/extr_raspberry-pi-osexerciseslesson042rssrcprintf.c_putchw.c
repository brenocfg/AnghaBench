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
typedef  int /*<<< orphan*/  (* putcf ) (void*,char) ;

/* Variables and functions */

__attribute__((used)) static void putchw(void *putp, putcf putf, int n, char z, char *bf) {
  char fc = z ? '0' : ' ';
  char ch;
  char *p = bf;
  while (*p++ && n > 0)
    n--;
  while (n-- > 0)
    putf(putp, fc);
  while ((ch = *bf++))
    putf(putp, ch);
}