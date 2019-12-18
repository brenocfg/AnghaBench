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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,size_t) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *
get_outfilename(mrb_state *mrb, char *infile, const char *ext)
{
  size_t infilelen;
  size_t extlen;
  char *outfile;
  char *p;

  infilelen = strlen(infile);
  extlen = strlen(ext);
  outfile = (char*)mrb_malloc(mrb, infilelen + extlen + 1);
  memcpy(outfile, infile, infilelen + 1);
  if (*ext) {
    if ((p = strrchr(outfile, '.')) == NULL)
      p = outfile + infilelen;
    memcpy(p, ext, extlen + 1);
  }

  return outfile;
}