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
 int /*<<< orphan*/  NUMBER1 ; 
 int /*<<< orphan*/  NUMBER10 ; 
 int /*<<< orphan*/  NUMBER11 ; 
 int /*<<< orphan*/  NUMBER2 ; 
 int /*<<< orphan*/  NUMBER3 ; 
 int /*<<< orphan*/  NUMBER4 ; 
 int /*<<< orphan*/  NUMBER5 ; 
 int /*<<< orphan*/  NUMBER6 ; 
 int /*<<< orphan*/  NUMBER7 ; 
 int /*<<< orphan*/  NUMBER8 ; 
 int /*<<< orphan*/  NUMBER9 ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char** strings ; 
 int /*<<< orphan*/  strtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * values1 ; 

void test1() {
  int i;
  for(i = 0; strings[i] ; i++) {
    char *s = strings[i];

    if(unlikely(!strcmp(s, "cache")))
      values1[i] = strtoull(NUMBER1, NULL, 10);

    else if(unlikely(!strcmp(s, "rss")))
      values1[i] = strtoull(NUMBER2, NULL, 10);
    
    else if(unlikely(!strcmp(s, "rss_huge")))
      values1[i] = strtoull(NUMBER3, NULL, 10);
  
    else if(unlikely(!strcmp(s, "mapped_file")))
      values1[i] = strtoull(NUMBER4, NULL, 10);
    
    else if(unlikely(!strcmp(s, "writeback")))
      values1[i] = strtoull(NUMBER5, NULL, 10);
    
    else if(unlikely(!strcmp(s, "dirty")))
      values1[i] = strtoull(NUMBER6, NULL, 10);
    
    else if(unlikely(!strcmp(s, "swap")))
      values1[i] = strtoull(NUMBER7, NULL, 10);
    
    else if(unlikely(!strcmp(s, "pgpgin")))
      values1[i] = strtoull(NUMBER8, NULL, 10);
    
    else if(unlikely(!strcmp(s, "pgpgout")))
      values1[i] = strtoull(NUMBER9, NULL, 10);
    
    else if(unlikely(!strcmp(s, "pgfault")))
      values1[i] = strtoull(NUMBER10, NULL, 10);
    
    else if(unlikely(!strcmp(s, "pgmajfault")))
      values1[i] = strtoull(NUMBER11, NULL, 10);
  }
}