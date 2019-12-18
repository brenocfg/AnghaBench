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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int UZLIB_OK ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ fwrite (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int /*<<< orphan*/  uz_free (int /*<<< orphan*/ *) ; 
 scalar_t__ uz_malloc (scalar_t__) ; 
 int uzlib_compress (int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 

int main (int argc, char **argv) {
  const char *in = argv[1], *out = argv[2];
  if (argc!=3)
    return 1;
  printf ("Compressing in=%s out=%s\n", in, out);
  FILE *fin, *fout;
  int status = -1;
  uint32_t iLen, oLen;
  uint8_t *iBuf, *oBuf;

  if (!(fin = fopen(in, "rb")) || fseek(fin, 0, SEEK_END) ||
      (iLen = ftell(fin)) <= 0  || fseek(fin, 0, SEEK_SET))
    return 1;
  if ((fout = fopen(out, "wb")) == NULL ||
      (iBuf = (uint8_t *) uz_malloc(iLen)) == NULL ||
      fread(iBuf, 1, iLen, fin) != iLen)
    return 1;

  if (uzlib_compress (&oBuf, &oLen, iBuf, iLen) == UZLIB_OK &&
      oLen == fwrite(oBuf, oLen, 1, fout))
    status = UZLIB_OK;
  uz_free(iBuf);
  if (oBuf) uz_free(oBuf);

  fclose(fin);
  fclose(fout);

  if (status == UZLIB_OK)
    unlink(out);

  return (status == UZLIB_OK) ? 1: 0;
}