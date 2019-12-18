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
struct TYPE_2__ {char* key; } ;
typedef  TYPE_1__ collator_sort_key_index_t ;

/* Variables and functions */
 int strcmp (char*,char*) ; 

__attribute__((used)) static int collator_cmp_sort_keys( const void *p1, const void *p2 )
{
	char* key1 = ((collator_sort_key_index_t*)p1)->key;
	char* key2 = ((collator_sort_key_index_t*)p2)->key;

	return strcmp( key1, key2 );
}