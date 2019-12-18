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
typedef  scalar_t__ uint32_t ;

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
 scalar_t__ cache_hash ; 
 scalar_t__ dirty_hash ; 
 scalar_t__ mapped_file_hash ; 
 scalar_t__ pgfault_hash ; 
 scalar_t__ pgmajfault_hash ; 
 scalar_t__ pgpgin_hash ; 
 scalar_t__ pgpgout_hash ; 
 scalar_t__ rss_hash ; 
 scalar_t__ rss_huge_hash ; 
 scalar_t__ simple_hash (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char** strings ; 
 int /*<<< orphan*/  strtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ swap_hash ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * values3 ; 
 scalar_t__ writeback_hash ; 

void test3() {
  int i;
  for(i = 0; strings[i] ; i++) {
    char *s = strings[i];
    uint32_t hash = simple_hash(s);

    if(unlikely(hash == cache_hash && !strcmp(s, "cache")))
      values3[i] = strtoull(NUMBER1, NULL, 10);
    
    else if(unlikely(hash == rss_hash && !strcmp(s, "rss")))
      values3[i] = strtoull(NUMBER2, NULL, 10);
    
    else if(unlikely(hash == rss_huge_hash && !strcmp(s, "rss_huge")))
      values3[i] = strtoull(NUMBER3, NULL, 10);
    
    else if(unlikely(hash == mapped_file_hash && !strcmp(s, "mapped_file")))
      values3[i] = strtoull(NUMBER4, NULL, 10);
    
    else if(unlikely(hash == writeback_hash && !strcmp(s, "writeback")))
      values3[i] = strtoull(NUMBER5, NULL, 10);
    
    else if(unlikely(hash == dirty_hash && !strcmp(s, "dirty")))
      values3[i] = strtoull(NUMBER6, NULL, 10);
    
    else if(unlikely(hash == swap_hash && !strcmp(s, "swap")))
      values3[i] = strtoull(NUMBER7, NULL, 10);
    
    else if(unlikely(hash == pgpgin_hash && !strcmp(s, "pgpgin")))
      values3[i] = strtoull(NUMBER8, NULL, 10);
    
    else if(unlikely(hash == pgpgout_hash && !strcmp(s, "pgpgout")))
      values3[i] = strtoull(NUMBER9, NULL, 10);
    
    else if(unlikely(hash == pgfault_hash && !strcmp(s, "pgfault")))
      values3[i] = strtoull(NUMBER10, NULL, 10);
    
    else if(unlikely(hash == pgmajfault_hash && !strcmp(s, "pgmajfault")))
      values3[i] = strtoull(NUMBER11, NULL, 10);
  }
}