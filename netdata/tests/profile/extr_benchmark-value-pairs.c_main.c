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
struct TYPE_2__ {char* name; void* hash; } ;

/* Variables and functions */
 void* active_anon_hash ; 
 void* active_file_hash ; 
 int /*<<< orphan*/  begin_clock () ; 
 void* cache_hash ; 
 void* dirty_hash ; 
 unsigned long end_clock () ; 
 void* hierarchical_memory_limit_hash ; 
 void* inactive_anon_hash ; 
 void* inactive_file_hash ; 
 void* mapped_file_hash ; 
 TYPE_1__* pairs ; 
 void* pgfault_hash ; 
 void* pgmajfault_hash ; 
 void* pgpgin_hash ; 
 void* pgpgout_hash ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* rss_hash ; 
 void* rss_huge_hash ; 
 void* simple_hash (char*) ; 
 int /*<<< orphan*/  simple_hash2 (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* swap_hash ; 
 int /*<<< orphan*/  test1 () ; 
 int /*<<< orphan*/  test2 () ; 
 int /*<<< orphan*/  test3 () ; 
 int /*<<< orphan*/  test4 () ; 
 int /*<<< orphan*/  test5 () ; 
 int /*<<< orphan*/  test6 () ; 
 int /*<<< orphan*/  test7 () ; 
 int /*<<< orphan*/  test8 () ; 
 int /*<<< orphan*/  test9 () ; 
 void* total_active_anon_hash ; 
 void* total_active_file_hash ; 
 void* total_cache_hash ; 
 void* total_dirty_hash ; 
 void* total_inactive_anon_hash ; 
 void* total_inactive_file_hash ; 
 void* total_mapped_file_hash ; 
 void* total_pgfault_hash ; 
 void* total_pgmajfault_hash ; 
 void* total_pgpgin_hash ; 
 void* total_pgpgout_hash ; 
 void* total_rss_hash ; 
 void* total_rss_huge_hash ; 
 void* total_swap_hash ; 
 void* total_unevictable_hash ; 
 void* total_writeback_hash ; 
 void* unevictable_hash ; 
 int /*<<< orphan*/ * values1 ; 
 int /*<<< orphan*/ * values2 ; 
 int /*<<< orphan*/ * values3 ; 
 int /*<<< orphan*/ * values4 ; 
 int /*<<< orphan*/ * values5 ; 
 int /*<<< orphan*/ * values6 ; 
 int /*<<< orphan*/ * values7 ; 
 int /*<<< orphan*/ * values8 ; 
 int /*<<< orphan*/ * values9 ; 
 void* writeback_hash ; 

int main(void)
{
    {
        int i;
        for(i = 0; pairs[i].name; i++)
            pairs[i].hash = simple_hash(pairs[i].name);
    }

    cache_hash = simple_hash("cache");
    rss_hash = simple_hash("rss");
    rss_huge_hash = simple_hash("rss_huge");
    mapped_file_hash = simple_hash("mapped_file");
    writeback_hash = simple_hash("writeback");
    dirty_hash = simple_hash("dirty");
    swap_hash = simple_hash("swap");
    pgpgin_hash = simple_hash("pgpgin");
    pgpgout_hash = simple_hash("pgpgout");
    pgfault_hash = simple_hash("pgfault");
    pgmajfault_hash = simple_hash("pgmajfault");
    inactive_anon_hash = simple_hash("inactive_anon");
    active_anon_hash = simple_hash("active_anon");
    inactive_file_hash = simple_hash("inactive_file");
    active_file_hash = simple_hash("active_file");
    unevictable_hash = simple_hash("unevictable");
    hierarchical_memory_limit_hash = simple_hash("hierarchical_memory_limit");
    total_cache_hash = simple_hash("total_cache");
    total_rss_hash = simple_hash("total_rss");
    total_rss_huge_hash = simple_hash("total_rss_huge");
    total_mapped_file_hash = simple_hash("total_mapped_file");
    total_writeback_hash = simple_hash("total_writeback");
    total_dirty_hash = simple_hash("total_dirty");
    total_swap_hash = simple_hash("total_swap");
    total_pgpgin_hash = simple_hash("total_pgpgin");
    total_pgpgout_hash = simple_hash("total_pgpgout");
    total_pgfault_hash = simple_hash("total_pgfault");
    total_pgmajfault_hash = simple_hash("total_pgmajfault");
    total_inactive_anon_hash = simple_hash("total_inactive_anon");
    total_active_anon_hash = simple_hash("total_active_anon");
    total_inactive_file_hash = simple_hash("total_inactive_file");
    total_active_file_hash = simple_hash("total_active_file");
    total_unevictable_hash = simple_hash("total_unevictable");

    // cache functions
    (void)simple_hash2("hello world");
    (void)strcmp("1", "2");
    (void)strtoull("123", NULL, 0);

  unsigned long i, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0, c9 = 0;
  unsigned long max = 1000000;

  begin_clock();
  for(i = 0; i <= max ;i++) test1();
  c1 = end_clock();

  begin_clock();
  for(i = 0; i <= max ;i++) test2();
  c2 = end_clock();
    
  begin_clock();
  for(i = 0; i <= max ;i++) test3();
  c3 = end_clock();

  begin_clock();
  for(i = 0; i <= max ;i++) test4();
  c4 = end_clock();

  begin_clock();
  for(i = 0; i <= max ;i++) test5();
  c5 = end_clock();

    begin_clock();
    for(i = 0; i <= max ;i++) test6();
    c6 = end_clock();

    begin_clock();
    for(i = 0; i <= max ;i++) test7();
    c7 = end_clock();

    begin_clock();
    for(i = 0; i <= max ;i++) test8();
    c8 = end_clock();

    begin_clock();
    for(i = 0; i <= max ;i++) test9();
    c9 = end_clock();

    for(i = 0; i < 11 ; i++)
        printf("value %lu: %llu %llu %llu %llu %llu %llu %llu %llu %llu\n", i, values1[i], values2[i], values3[i], values4[i], values5[i], values6[i], values7[i], values8[i], values9[i]);
  
  printf("\n\nRESULTS\n");
  printf("test1() [1] in %lu usecs: simple system strcmp().\n"
         "test2() [4] in %lu usecs: inline simple_hash() with system strtoull().\n"
         "test3() [5] in %lu usecs: statement expression simple_hash(), system strtoull().\n"
         "test4() [6] in %lu usecs: inline simple_hash(), if-continue checks.\n"
         "test5() [7] in %lu usecs: inline simple_hash(), if-else-if-else-if (netdata default prior to ARL).\n"
         "test6() [8] in %lu usecs: adaptive re-sortable array with strtoull() (wow!)\n"
         "test7() [9] in %lu usecs: adaptive re-sortable array with str2ull() (wow!)\n"
         "test8() [2] in %lu usecs: nested loop with strtoull()\n"
         "test9() [3] in %lu usecs: nested loop with str2ull()\n"
         , c1
         , c2
         , c3
         , c4
         , c5
         , c6
         , c7
         , c8
         , c9
         );

  return 0;
}