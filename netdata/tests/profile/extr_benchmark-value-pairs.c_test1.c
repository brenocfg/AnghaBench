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
struct TYPE_2__ {char* name; char* value; } ;

/* Variables and functions */
 TYPE_1__* pairs ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strtoull (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * values1 ; 

void test1() {
  int i;
  for(i = 0; pairs[i].name ; i++) {
    const char *s = pairs[i].name;
    const char *v = pairs[i].value;

    if(unlikely(!strcmp(s, "cache")))
      values1[i] = strtoull(v, NULL, 10);

    else if(unlikely(!strcmp(s, "rss")))
      values1[i] = strtoull(v, NULL, 10);
    
    else if(unlikely(!strcmp(s, "rss_huge")))
      values1[i] = strtoull(v, NULL, 10);
  
    else if(unlikely(!strcmp(s, "mapped_file")))
      values1[i] = strtoull(v, NULL, 10);
    
    else if(unlikely(!strcmp(s, "writeback")))
      values1[i] = strtoull(v, NULL, 10);
    
    else if(unlikely(!strcmp(s, "dirty")))
      values1[i] = strtoull(v, NULL, 10);
    
    else if(unlikely(!strcmp(s, "swap")))
      values1[i] = strtoull(v, NULL, 10);
    
    else if(unlikely(!strcmp(s, "pgpgin")))
      values1[i] = strtoull(v, NULL, 10);
    
    else if(unlikely(!strcmp(s, "pgpgout")))
      values1[i] = strtoull(v, NULL, 10);
    
    else if(unlikely(!strcmp(s, "pgfault")))
      values1[i] = strtoull(v, NULL, 10);
    
    else if(unlikely(!strcmp(s, "pgmajfault")))
      values1[i] = strtoull(v, NULL, 10);
  }
}