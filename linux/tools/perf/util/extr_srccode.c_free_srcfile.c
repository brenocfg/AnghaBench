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
struct srcfile {int /*<<< orphan*/  fn; int /*<<< orphan*/  lines; scalar_t__ maplen; int /*<<< orphan*/  map; int /*<<< orphan*/  hash_nd; int /*<<< orphan*/  nd; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct srcfile*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_total_sz ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  num_srcfiles ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_srcfile(struct srcfile *sf)
{
	list_del_init(&sf->nd);
	hlist_del(&sf->hash_nd);
	map_total_sz -= sf->maplen;
	munmap(sf->map, sf->maplen);
	zfree(&sf->lines);
	zfree(&sf->fn);
	free(sf);
	num_srcfiles--;
}