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
 int* bytes64 ; 
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static char *base64Encode(char *data, unsigned int len) {
  int blen = (len + 2) / 3 * 4;

  char *out = (char *) calloc(1,blen + 1);
  out[blen] = '\0';
  int j = 0, i;
  for (i = 0; i < len; i += 3) {
    int a = data[i];
    int b = (i + 1 < len) ? data[i + 1] : 0;
    int c = (i + 2 < len) ? data[i + 2] : 0;
    out[j++] = bytes64[a >> 2];
    out[j++] = bytes64[((a & 3) << 4) | (b >> 4)];
    out[j++] = (i + 1 < len) ? bytes64[((b & 15) << 2) | (c >> 6)] : 61;
    out[j++] = (i + 2 < len) ? bytes64[(c & 63)] : 61;
  }

  return out; // Requires free
}