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
typedef  TYPE_1__* xsltTemplatePtr ;
struct TYPE_3__ {scalar_t__ mode; scalar_t__ match; } ;

/* Variables and functions */

__attribute__((used)) static char *
pretty_templ_match(xsltTemplatePtr templ) {
  static char dst[1001];
  char *src = (char *)templ->match;
  int i=0,j;

  /* strip white spaces */
  for (j=0; i<1000 && src[j]; i++,j++) {
      for(;src[j]==' ';j++);
      dst[i]=src[j];
  }
  if(i<998 && templ->mode) {
    /* append [mode] */
    dst[i++]='[';
    src=(char *)templ->mode;
    for (j=0; i<999 && src[j]; i++,j++) {
      dst[i]=src[j];
    }
    dst[i++]=']';
  }
  dst[i]='\0';
  return dst;
}